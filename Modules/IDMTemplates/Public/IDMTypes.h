#pragma once

// ============ INCLUDES ============
#include <sqlite3.h>

#include <string>
#include <map>
#include <functional>
#include <memory>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <string_view>
#include <type_traits>

#include <stdexcept>
#include <sqlite3.h>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>

#include <json.hpp>
using json = nlohmann::json;

namespace IDMTemplates
{

// ============ DATA STRUCT PROPERTY MACRO ============
/*
 * IDM_PROPERTY(Type, MemberName, ColumnIndex)
 * 
 * Generates a private member variable with public getter/setter and column metadata.
 * 
 * Generates:
 *   - Get##MemberName(): const getter returning the member value
 *   - Set##MemberName(Type): setter updating the member value
 *   - GetColumnIndex_##MemberName(): static constexpr returning ColumnIndex for schema mapping
 * 
 * Example: IDM_PROPERTY(std::string, Name, 0)
 * Generates: m_Name, GetName(), SetName(const std::string&), GetColumnIndex_Name() -> 0
 */
#define IDM_PROPERTY_ACCESSORS(Type, MemberName, ColumnIndex) \
public: \
    Type Get##MemberName() const { return MemberName; } \
    void Set##MemberName(Type value) { MemberName = value; } \
    static constexpr size_t GetColumnIndex_##MemberName() { return ColumnIndex; }

struct RouteResult {

    sqlite3* db;
    bool writable;
    std::string resolvedPath;
    std::string parentId;
    std::string dynamicTableName;
    bool isCollection = false;
    std::string tableName = "";
};

class IDatabaseRouter {
public:


    virtual ~IDatabaseRouter() = default;
    virtual RouteResult Route(const std::string& path, bool isWrite = false) = 0;
    virtual RouteResult Route(const std::vector<std::string>& pathTokens, bool isWrite = false) = 0;
    virtual std::string ResolveTableName(const std::string& path) = 0;

};




// ============ BASE INTERFACE ============
class DataTypeDef {
public:
    virtual ~DataTypeDef() = default;
    virtual const char* GetStaticTableName() const = 0;
    virtual bool CreateTable(sqlite3* db, const std::string& tableName) const = 0;
    virtual bool Load(sqlite3* db, const std::string& tableName, const std::string& whereClause, void* targetObject) const = 0;
    virtual bool Save(sqlite3* db, const std::string& tableName, const void* object) const = 0;
    virtual bool Delete(sqlite3* db, const std::string& tableName, const void* object) const = 0;

    virtual bool ImportJson(void* targetObject, const nlohmann::json& json) const = 0;
};

// ============ PROPERTY WRAPPER ============
template<typename ValueType, auto MemberPtr, size_t ColumnIndex>
struct Property {
    using Type = ValueType;
    static constexpr auto Member = MemberPtr;
    static constexpr size_t Index = ColumnIndex;
};

// ============ TABLE METADATA WRAPPER ============
struct ColumnDescriptor {
    const char* name;
    const char* sqlDef;
};

struct TableRoute
{
    std::string_view Path;
    std::string_view Database;
    std::string_view TableName; 
    bool ForCollection = false;
    const ColumnDescriptor* columns = nullptr;
    size_t columnCount = 0;

    void RegisterRoute() const;
};

struct TableMetadata {
    const TableRoute* Route;
    const ColumnDescriptor* Columns;
    size_t ColumnCount;
    

    constexpr TableMetadata(const TableRoute* route, const ColumnDescriptor* cols, size_t count)
        : Route(route), Columns(cols), ColumnCount(count) 
    {}
};






};



namespace IDMRouting {
    enum class SegmentType { Literal, Wildcard, ResourceId, ResourceType };

    struct PathSegment {
        SegmentType type;
        std::string value;  // For Literal and ResourceType
    };
    

struct RouteEntry {
    std::vector<std::string> tokens;
    std::string targetDatabase;
    std::string targetTable;
    bool isCollection = false;
    const IDMTemplates::ColumnDescriptor* columns = nullptr;
    size_t columnCount = 0;
    
    std::vector<PathSegment> path;
    int parentIdTokenIndex = -1;
    uint64_t pathHash = 0;
};
    
    static std::unordered_map<uint64_t, RouteEntry> g_rulesByHash;
    static std::vector<RouteEntry> g_rulesOrdered;
    
    static uint64_t HashTokens(const std::vector<std::string>& tokens) {
        std::hash<std::string> hasher;
        uint64_t hash = 0;
        for (size_t i = 0; i < tokens.size(); ++i) {
            hash ^= (hasher(tokens[i]) << (i & 7));
        }
        return hash;
    }
    
    static std::vector<std::string> TokenizePath(const std::string& path) {
        std::vector<std::string> tokens;
        size_t start = 0, end = 0;
        while ((end = path.find('/', start)) != std::string::npos) {
            if (end > start) tokens.push_back(path.substr(start, end - start));
            start = end + 1;
        }
        if (start < path.length()) tokens.push_back(path.substr(start));
        return tokens;
    }
}


class PathToken {
public:
    enum class Type { Literal, Wildcard, RowId, Insignificant };
    Type type;
    std::string value;
    
    PathToken(Type t, const std::string& v = "") : type(t), value(v) {}
};

class PathRule {
public:
    std::vector<PathToken> tokens;
    std::string targetDatabase;
    std::string targetTable;
    bool isCollection = false;
    int specificity = 0;
    
    static inline PathRule Parse(const std::string& pathSpec, 
                         const std::string& db, 
                         const std::string& table,
                         bool collection = false) {
        PathRule rule;
        rule.targetDatabase = db;
        rule.targetTable = table;
        rule.isCollection = collection;
        
        std::istringstream iss(pathSpec);
        std::string segment;
        int depth = 0;
        
        while (std::getline(iss, segment, '/')) {
            if (segment.empty()) continue;
            
            if (segment == "@") {
                rule.tokens.push_back(PathToken(PathToken::Type::RowId));
                rule.specificity += 10;
            } else if (segment == "$" + table) {
                rule.tokens.push_back(PathToken(PathToken::Type::Insignificant, table));
                rule.isCollection = true;
            } else if (segment[0] == '{' && segment.back() == '}') {
                rule.tokens.push_back(PathToken(PathToken::Type::Wildcard, segment.substr(1, segment.length() - 2)));
                rule.specificity += 5;
            } else {
                rule.tokens.push_back(PathToken(PathToken::Type::Literal, segment));
                rule.specificity += 20;
            }
            depth++;
        }
        
        return rule;
    }
};




class IDMShard {
public:
    IDMShard(std::shared_ptr<IDMTemplates::IDatabaseRouter> router, const std::string& path):m_router(router),m_path(path)
    {

    };
    virtual json ExportJson() = 0;
    virtual void ImportJson(const json& jsonObj) = 0;
    virtual void Save() = 0;
    virtual void Load() = 0;
    virtual void DeleteShard() = 0;


    IDMTemplates::IDatabaseRouter* GetRouter(){ if(m_router){return m_router.get();} return nullptr; };
    const std::string& GetPath() const {return m_path;};
    std::vector<PathToken>& GetTokenizedPath(){return m_pathTokenized;};

    std::shared_ptr<IDMTemplates::IDatabaseRouter> m_router;
    std::string m_path;
    std::vector<PathToken> m_pathTokenized;
};

class IDMObject : public IDMShard{
public:
    IDMObject(std::shared_ptr<IDMTemplates::IDatabaseRouter> router, const std::string& path):IDMShard(router, path)
    {

    };
    virtual IDMShard* GetShard(const std::string& path) = 0;

    virtual json ExportAllJson() = 0;
    virtual void ImportAllJson(const json& jsonObj) = 0;
    virtual void SaveAll() = 0;
    virtual void LoadAll() = 0;

    virtual void DeleteObject() = 0;

};

template <typename T>
class IDMObject_Inst
{
    std::string Path;
    std::shared_ptr<T> Instance;

    static inline std::function<T*(const std::string&)> Resolver;
    static inline std::function<T*(const std::string&, const std::string&, const json&)> Factory;
    static inline std::function<bool(const std::string&)> Deleter;

public:
    static void Register(
        std::function<T*(const std::string&)> resolver, 
        std::function<T*(const std::string&, const std::string&, const json&)> factory,
        std::function<bool(const std::string&)> deleter)
    {
        Resolver = resolver;
        Factory = factory;
        Deleter = deleter;
    }

    T* Get()
    {
        if (Instance) {
            return Instance.get();
        }
        return Resolve(Path);
    }

    static T* CreateNew(const std::string& Package, const std::string& Name, const json& Init = json()) {
        if (!Factory) return nullptr;
        return Factory(Package, Name, Init);

    }

    static T* Resolve(const std::string& Path) {
        if (!Resolver) return nullptr;
        return Resolver(Path);

    }

    static bool DeleteData(const std::string& Path) {
        if (!Deleter) return false;
        return Deleter(Path);
    }
};

