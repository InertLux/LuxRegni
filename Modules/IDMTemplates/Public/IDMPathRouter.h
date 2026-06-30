#pragma once

#include <sqlite3.h>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>
#include <IDMTypes.h>

#include <json.hpp>
using json = nlohmann::json;

struct TargetMetadata
{
    std::string targetName;
    std::string schemaVersion;
    int64_t createdAt;
    int64_t lastModified;
};



// ============ DATABASE ROUTER INTERFACE ============
/*
The Router stands as the IO path resolution between Target Instance, and data backend (wherever it is physically stored.)
Following the tripartite 'Fragment' Structure of Root, Base, Shard. The Database Fragment exists in degrees of duplicated state. this is fully intentional As The need to have a single point of truth, an understandable canvas, then following emergent story state and other 'Temporal' changes. This is a Delta forward approach that 'merges' changes heirarchally. 
 In this way tranmission of mutations is very cheap. though at some performance cost. 
The lifecycle of this class is expected to be fully managed by User Target specific Game Instance. It is an interface, only because System FilePath IO will need to be specific to platform. 
*/
// ============ DATABASE ROUTER INTERFACE ============
class DatabaseRouterImpl : public IDMTemplates::IDatabaseRouter{
public:
    virtual ~DatabaseRouterImpl() = default;
    
    enum class Target { Root, Base, Shard };

protected:
    Target m_currentTarget = Target::Shard;
    std::string m_activeBaseName = "none";
    std::string m_activeShardName = "none";
    std::string m_projectRoot;
    std::string m_baseDataPath;
    std::unordered_map<std::string, sqlite3*> m_dbCache;
    sqlite3* m_metadataDb = nullptr;


public:
    
    static  std::string SafeNameFromPath(const std::string& path);
    
    static  bool MatchesRule(const std::vector<std::string>& pathTokens, const std::vector<std::string>& ruleTokens);
protected:    
     std::vector<std::string> TokenizePath(const std::string& path);
    
     uint64_t HashTokens(const std::vector<std::string>& tokens);
public: 
     bool InitializeMetadataDatabase();


    
public:
static std::vector<IDMRouting::PathSegment> ParsePathTemplate(const std::string& pathSpec);
static void RegisterRoute(const std::string& pathSpec,
                          const std::string& database,
                          const std::string& table,
                          const IDMTemplates::ColumnDescriptor* cols,
                          size_t colCount,
                          bool isCollection = false) ;
    
    static std::vector<std::string> ParsePath(const std::string& path);

    virtual std::string ResolveTableName(const std::string& path) override;


    
     virtual IDMTemplates::RouteResult Route(const std::string& path, bool isWrite = false) override;

     virtual IDMTemplates::RouteResult Route(const std::vector<std::string>& pathTokens, bool isWrite = false) override;
public: 

     bool InitializeProject(const std::string& projectPath, const std::string& schemaVersion);
     bool CreateNewBase(const std::string& baseName, const std::string& schemaVersion);

     bool CreateNewShard(const std::string& shardName, const std::string& schemaVersion);
    
     bool RecordTargetMetadata(const std::string& targetName, const std::string& schemaVersion);

     bool UpdateTargetSchemaVersion(const std::string& targetName, const std::string& newVersion);
    
     bool GetTargetMetadata(const std::string& targetName, TargetMetadata& outMeta);

public: 

     bool CreateNewTarget(const std::string& basePath);

     bool AuditTarget(const std::string& basePath, 
                             const std::function<bool(sqlite3*, const IDMRouting::RouteEntry&)>& auditFn);
    template<typename DataTypeImpl>
     bool CreateTablesForTarget(const std::string& basePath);


public:

     IDMTemplates::RouteResult ResolveRoute(const IDMRouting::RouteEntry& rule, 
                            const std::vector<std::string>& pathTokens, 
                            bool isWrite);
    
     sqlite3* GetOrOpenDatabase(const std::string& dbPath);
    
     std::string GetFragmentRootPath(Target target);

    virtual void PlatformEnsureDirectoryExists(const std::string& dirPath) = 0;
    virtual sqlite3* PlatformOpenDatabase(const std::string& filePath) = 0;
    virtual void CloseAllDatabases() = 0;
};
