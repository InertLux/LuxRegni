#pragma once

// ============ INCLUDES ============
#include <sqlite3.h>
#include <json.hpp>
#include <Conversions.hpp>
#include <IDMTypes.h>
#include <SQLTableInterface.hpp>
#include <IDMPathRouter.h>
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

#include <json.hpp>
using json = nlohmann::json;

namespace IDMTemplates
{

// ============ SUBTYPE, AS OOP DATA SHARD ============
//This will create a new table following parent path with Table name as declared in the SQL definition 
// Follows a direct 1 Root - 1 Item 
// Not using symbolic links instead following rules based approach using 1 path 1 object   
// ============ SHARD WITH LIFECYCLE & ROUTING ============
template<typename ObjectType, typename TableDefinition>
class Shard : public IDMShard{
public:
    using DataType = ObjectType;
    using MetaData = TableDefinition;


    // Constructor now takes router + path; database is resolved at query time
    Shard(std::shared_ptr<DatabaseRouterImpl> router, const std::string& path) 
        : IDMShard(std::static_pointer_cast<IDatabaseRouter>(router), path), 
          m_definition(std::make_unique<TableDefinition>()) {}
    
    virtual ~Shard() = default;
    
    // ========== ACCESSORS ==========
    ObjectType& GetData(){return m_data;};
        
    // ========== CONTEXT ACCESSORS ==========
    
    static constexpr char* SubtypeName() { return MetaData::GetMetadataTableName();}
    const char* GetTableName() const { return m_definition->GetTableName(); }

    static constexpr TableMetadata* GetMetadata() {return MetaData::GetMetadata(); }
    static constexpr TableDefinition* GetDefinition(){return MetaData::GetMetadata();}
    static constexpr TableRoute* GetRoute(){return MetaData::GetRoute(); }
    
    //IDMShard BEGIN
    virtual json ExportJson()  override {return json();};
    virtual void ImportJson(const json& jsonObj) override {};
    virtual void Save()  override {SaveImpl();};
    virtual void Load() override {LoadImpl();};
    virtual void DeleteShard() override {};
    //END


    // ========== DATABASE OPERATIONS ==========
    virtual void PreSave(){}
    virtual void PostLoad(){}

    void DeleteShardImpl() {
        auto route = this->GetRouter()->Route(GetPath(), true);
        if (!route.db || !route.writable) return;
        
        m_definition->Delete(route.db, route.tableName, this);
    }

    virtual bool LoadImpl(){
        auto route = this->GetRouter()->Route(GetPath(), false);
        if (!route.db) return false;

        if (!m_definition->Load(route.db, route.tableName, "path = '" + GetPath() + "'", &m_data)) {
            return false;
        }
        PostLoad();
        return true;
    }
    virtual bool SaveImpl() {
        PreSave();
        auto route = this->GetRouter()->Route(GetPath(), true);
        if (!route.db || !route.writable) return false;
        
        return m_definition->Save(route.db, route.tableName, &m_data);
    }
protected:
    DataType m_data;
    std::unique_ptr<TableDefinition> m_definition;
};






// ============ SUBTYPE. LINKED COLLECTION. ============
//  This will create a new TABLE per Root Item   
//  /Place/Base/Whiterun/Chunks/0_0 <- storing a chunk array contained in place row of id == whiterun
//  Collections... The sane way. 
//      Rather than bloating your primary DATABASE with a ton of collections... instead utilize router to create a single DATABASE per use/domain
//      For example: /Place/Base (Base content package) would get it's own SQLite database created to store collections in that path space. 
// ============ SHARD WITH LIFECYCLE & ROUTING ============
template<typename ChildObjectType, typename ChildTableDefinition, typename ShardType = Shard<ChildObjectType, ChildTableDefinition>>
class CollectionShard : public ShardType {
public:
    using BaseType = ShardType;
    
    using ChildType = ChildObjectType;
    using ChildTableDef = ChildTableDefinition;
    CollectionShard(std::shared_ptr<DatabaseRouterImpl> router, 
                   const std::string& parentPath)
        : BaseType(router, parentPath),
          m_parentPath(parentPath)
    {
    }
    
    virtual ~CollectionShard() = default;
    
    // ========== PATH CONSTRUCTION ==========
    
    std::string ConstructChildPath(const std::string& childId) const {
        return m_parentPath + "/" + m_collectionKey + "/" + childId;
    }
    std::string ConstructParentPattern() const {
        return m_parentPath + "/" + m_collectionKey + "/%";
    }
    
    // ========== BATCH OPERATIONS ==========
    
    /// Load all children for this parent into m_children
    bool LoadAllChildren();
    /// Save all loaded children to database
    bool SaveAllChildren();
    
    // ========== COLLECTION MUTATION ==========
    /// Add a new child to the collection
    bool AddChild(const std::string& childId, const ChildObjectType& childData);
    /// Remove a child by ID from collection (memory only; use SaveAllChildren to persist)
    bool RemoveChildById(const std::string& childId);
    // ========== ACCESSORS ==========
    const std::vector<std::unique_ptr<ChildObjectType>>& GetChildren() const;
    size_t GetChildCount() const;
    const std::string& GetParentPath() const;
    const std::string& GetCollectionKey() const;
    bool CreateChildTable() const;   
    bool LoadItem(ChildObjectType*& outObject) const;
    bool SaveItem(const ChildObjectType* object) const;

protected:
    std::string m_parentPath;
    std::string m_collectionKey;
    std::vector<std::unique_ptr<ChildObjectType>> m_children;
};


#include "../Private/Templates/IDMCollection_IMPL.tpp"


// ============ ROOT 'BASE' TYPE ============
// base root object used to define a path domain. 
//  for example I may create 
//  - Module Place -> /Place/Base/placeid 
//                  base atomic unit used to store data related to a Place as concept.
//  - Module Item -> /Item/Base/itemid 
//                  base atomic unit used to store data related to a Item as concept.
//  - Module Schematic -> /Schematic/Base/Schematicid 
//                  base atomic unit used to store data related to area schematics as concept.
// ============ BASE TYPE TEMPLATE WITH SUPPORT FOR SHARDS AND COLLECTIONS ============
template<typename RootDataType, typename RootTableDef, typename... SubtypeShards>
class RootObject : public IDMObject{
protected:

    RootDataType m_data;
    std::unique_ptr<RootTableDef> m_rootDefinition;
    std::tuple<std::unique_ptr<SubtypeShards>...> m_subtypes;

private:
    template<size_t... Is>
    void InitializeSubtypes(std::index_sequence<Is...>, 
                           std::shared_ptr<DatabaseRouterImpl> router,
                           const std::string& path) {
        m_subtypes = std::make_tuple(
            std::make_unique<std::tuple_element_t<Is, std::tuple<SubtypeShards...>>>(
                router, path
            )...
        );
    }

public:
    RootObject(std::shared_ptr<DatabaseRouterImpl> router, const std::string& path)
        : IDMObject(std::static_pointer_cast<IDatabaseRouter>(router), path),
          m_rootDefinition(std::make_unique<RootTableDef>()) 
    {
        InitializeSubtypes(std::index_sequence_for<SubtypeShards...>{}, router, path);
    }

    virtual ~RootObject() = default;


    template<typename ShardType>
    ShardType* GetShard() {
        return std::get<std::unique_ptr<ShardType>>(m_subtypes).get();
    }

    virtual void PreSave() {}
    virtual void PostLoad() {}

        
    //IDMShard BEGIN

    virtual json ExportJson() override {return json();};
    virtual void ImportJson(const json& jsonObj) override {};
    virtual void Save() override {SaveImpl();};
    virtual void Load() override {LoadImpl();};
    virtual void DeleteShard() override {};
    //END
            
    //IDMObject BEGIN
    virtual IDMShard* GetShard(const std::string& path) override{return nullptr;};
    
    virtual json ExportAllJson()  override{return json();};
    virtual void ImportAllJson(const json& jsonObj)override {};
    virtual void SaveAll() override{SaveAllImpl();}
    virtual void LoadAll() override{LoadAllImpl();}
    virtual void DeleteObject() override{DeleteObjectImpl();};
    //END
    

    void DeleteObjectImpl() {
        auto route = this->GetRouter()->Route(GetPath(), true);
        if (!route.db || !route.writable) return;
        
        DeleteAllSubtypes(std::index_sequence_for<SubtypeShards...>{});
        m_rootDefinition->Delete(route.db, route.tableName, this);
    }
    void SaveImpl() {

        PreSave();
        auto route = this->GetRouter()->Route(GetPath(), true);
        if (!route.db || !route.writable) return;

        m_rootDefinition->Save(route.db, route.tableName, &m_data);
    }

    void LoadImpl() {
        auto route = this->GetRouter()->Route(GetPath(), true);
        if (!route.db || !route.writable) return;
        
        m_rootDefinition->Load(route.db, route.tableName, "path = '" + GetPath() + "'", &m_data);
        PostLoad();
    }


    bool LoadAllImpl() {
        auto route = this->GetRouter()->Route(GetPath(), true);
        if (!route.db || !route.writable) return false;
        

        std::string tableName = DatabaseRouterImpl::SafeNameFromPath(GetPath());
        if (!m_rootDefinition->Load(route.db, tableName, "path = '" + GetPath() + "'", &m_data)) 
            return false;

        LoadAllSubtypes(std::index_sequence_for<SubtypeShards...>{});
        PostLoad();
        return true;
    }
    
    bool SaveAllImpl() {
        PreSave();
        auto route = this->GetRouter()->Route(GetPath(), true);
        if (!route.db || !route.writable) return false;
        
        std::string tableName = route.tableName;
        if (!m_rootDefinition->Save(route.db, tableName, &m_data)) return false;
        SaveAllSubtypes(std::index_sequence_for<SubtypeShards...>{});
        return true;
    }
    

public:
    //Terminal overload
    void DeleteAllSubtypes(std::index_sequence<>) {}
    template<size_t I, size_t... Is>
    void DeleteAllSubtypes(std::index_sequence<I, Is...>) {
        DeleteSubtypeAt<I>();
        DeleteAllSubtypes(std::index_sequence<Is...>{});
    }
    template<size_t I>
    void DeleteSubtypeAt() {
        auto* shard = std::get<I>(m_subtypes).get();
        if (shard) shard->DeleteShard();
    }

    //Terminal overload
    void LoadAllSubtypes(std::index_sequence<>) {}
    template<size_t I, size_t... Is>
    void LoadAllSubtypes(std::index_sequence<I, Is...>) {
        LoadSubtypeAt<I>();
        LoadAllSubtypes(std::index_sequence<Is...>{});
    }
    template<size_t I>
    void LoadSubtypeAt() {
        auto* shard = std::get<I>(m_subtypes).get();
        if (shard) shard->Load();
    }
    
    //Terminal overload
    void SaveAllSubtypes(std::index_sequence<>) {}
    template<size_t I, size_t... Is>
    void SaveAllSubtypes(std::index_sequence<I, Is...>) {
        SaveSubtypeAt<I>();
        SaveAllSubtypes(std::index_sequence<Is...>{});
    }
    
    template<size_t I>
    void SaveSubtypeAt() {
        auto* shard = std::get<I>(m_subtypes).get();
        if (shard) shard->Save();
    }


public:
    static void RegisterAllRoutes() {
        RootTableDef::GetMetadata()->Route->RegisterRoute();
        RegisterAllSubtypeRoutes(std::index_sequence_for<SubtypeShards...>{});
    }

private:

    //Terminal overload
    static void RegisterAllSubtypeRoutes(std::index_sequence<>) {}
    template<size_t I, size_t... Is>
    static void RegisterAllSubtypeRoutes(std::index_sequence<I, Is...>) {
        RegisterSubtypeRouteAt<I>();
        RegisterAllSubtypeRoutes(std::index_sequence<Is...>{});
    }

    template<size_t I>
    static void RegisterSubtypeRouteAt() {
        using ShardType = std::tuple_element_t<I, std::tuple<SubtypeShards...>>;
        ShardType::MetaData::GetMetadata()->Route->RegisterRoute();
    }
    public:


};







}



