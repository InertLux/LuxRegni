#pragma once

#include <sqlite3.h>
#include <string>
#include <memory>
#include <tuple>
#include <cstddef>
#include <IDMTypes.h>
#include <IDMPathRouter.h>
#include "Conversions.hpp"
#include <json.hpp>
using json =  nlohmann::json;


namespace IDMTemplates {

/*
    This is a compile time MetaData + SQL + JSON importer.
    It is declared alongside struct Def and stores a template array of all IDM properties. And is able to access them quickly by index.
    
    DataConversions are handled in Conversions.hpp 
    Simply by overloading ExtractColumnValue and BindValue using your own type. 
*/

// ============ DATA TYPE IMPLEMENTATION ============
template<typename ObjectType, const TableMetadata* Meta, typename... Properties>
class DataTypeImpl : public DataTypeDef {
private:
    static constexpr size_t PropertyCount = sizeof...(Properties);
    
    static std::string BuildColumnDefs();


    template<typename Prop>
    void ExtractAndBind(ObjectType* obj, sqlite3_stmt* stmt) const;
    
    template<typename... Props, size_t... Is>
    void BindColumnsToObjectImpl(ObjectType* obj, sqlite3_stmt* stmt, 
                                IDMConversions::IndexSequence<Is...>) const;
    
    template<typename Prop>
    void BindMemberValue(const ObjectType* obj, sqlite3_stmt* stmt) const;
    
    template<typename... Props, size_t... Is>
    void BindMembersToStatementImpl(const ObjectType* obj, sqlite3_stmt* stmt,
                                   IDMConversions::IndexSequence<Is...>) const;
    
    bool LoadImpl(sqlite3* db, const std::string& tableName, 
                const std::string& whereClause, ObjectType* obj) const;
    bool SaveImpl(sqlite3* db, const std::string& tableName, 
                const ObjectType* obj) const;
    bool DeleteImpl(sqlite3* db, const std::string& tableName, 
    const ObjectType* obj) const;
private:
    template<typename Prop>
    void ImportJsonProperty(ObjectType* obj, const  json& json) const{};    
    template<typename... Props, size_t... Is>
    void ImportJsonImpl(ObjectType* obj, const  json& json,IDMConversions::IndexSequence<Is...>) const{}

public:
    bool ImportJson(void* targetObject, const  json& json) const override{return false;}

public:
    DataTypeImpl();
    virtual ~DataTypeImpl();

    const char* GetStaticTableName() const override;
    bool CreateTable(sqlite3* db, const std::string& tableName) const override;
    bool Load(sqlite3* db, const std::string& tableName, const std::string& whereClause, void* targetObject) const override;
    bool Save(sqlite3* db, const std::string& tableName, const void* object) const override;
    bool Delete(sqlite3* db, const std::string& tableName, const void* object) const override;


    static constexpr const TableMetadata* GetMetadata() { return Meta; }
    static constexpr const TableRoute* GetMetadataRoute() { return Meta->Route; }
    static constexpr const char* GetMetadataTableName() { return Meta->Route->TableName.data(); }
};

// ============ IMPLEMENTATION ============
#include "../Private/Templates/TableDef_IMPL.tpp"

} // namespace IDMTemplates

