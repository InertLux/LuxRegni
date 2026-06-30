#pragma once 


// LoadAllChildren

template<typename ChildObjectType, typename ChildTableDefinition, typename ShardType>
bool CollectionShard<ChildObjectType, ChildTableDefinition, ShardType>::LoadAllChildren() {
    auto route = this->m_router->Route(m_parentPath, false);
    if (!route.db) return false;

    m_children.clear();
    std::string tableName = this->m_definition->GetMetadataTableName();
    std::string pattern = ConstructParentPattern();
    std::string whereClause = "path LIKE '" + pattern + "'";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(route.db, 
        ("SELECT * FROM " + tableName + " WHERE " + whereClause).c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) return false;
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        auto child = std::make_unique<ChildObjectType>();
        this->m_definition->LoadItem(route.db, tableName, whereClause, child.get());
        m_children.push_back(std::move(child));
    }
    sqlite3_finalize(stmt);
    return true;
}


// SaveAllChildren

template<typename ChildObjectType, typename ChildTableDefinition, typename ShardType>
bool CollectionShard<ChildObjectType, ChildTableDefinition, ShardType>::SaveAllChildren() {
    auto route = this->m_router->Route(m_parentPath, true);
    if (!route.db || !route.writable) return false;

    std::string tableName = this->m_definition->GetMetadataTableName();
    this->m_definition->CreateTable(route.db, tableName);

    for (const auto& child : m_children) {
        if (!this->m_definition->SaveItem(route.db, tableName, child.get())) return false;
    }
    return true;
}

//AddChild

template<typename ChildObjectType, typename ChildTableDefinition, typename ShardType>
bool CollectionShard<ChildObjectType, ChildTableDefinition, ShardType>::AddChild(const std::string& childId, const ChildObjectType& childData) {
    auto route = this->m_router->Route(m_parentPath, true);
    if (!route.db || !route.writable) return false;
    
    auto mutableChild = std::make_unique<ChildObjectType>(childData);
    mutableChild->path = ConstructChildPath(childId);
    
    bool success = this->m_definition->Save(route.db, mutableChild.get());
    if (success) {
        m_children.push_back(std::move(mutableChild));
    }
    return success;
}

//RemoveChildById

template<typename ChildObjectType, typename ChildTableDefinition, typename ShardType>
bool CollectionShard<ChildObjectType, ChildTableDefinition, ShardType>::RemoveChildById(const std::string& childId) {
    auto it = std::find_if(m_children.begin(), m_children.end(),
        [this, &childId](const std::unique_ptr<ChildObjectType>& child) {
            return ConstructChildPath(childId) == child->path;
        });
    
    if (it != m_children.end()) {
        m_children.erase(it);
        return true;
    }
    return false;
}

// GetChildren

template<typename ChildObjectType, typename ChildTableDefinition, typename ShardType>
const std::vector<std::unique_ptr<ChildObjectType>>& CollectionShard<ChildObjectType, ChildTableDefinition, ShardType>::GetChildren() const {
    return m_children;
}

// GetChildCount

template<typename ChildObjectType, typename ChildTableDefinition, typename ShardType>
size_t CollectionShard<ChildObjectType, ChildTableDefinition, ShardType>::GetChildCount() const {
    return m_children.size();
}

//GetParentPath

template<typename ChildObjectType, typename ChildTableDefinition, typename ShardType>
const std::string& CollectionShard<ChildObjectType, ChildTableDefinition, ShardType>::GetParentPath() const {
    return m_parentPath;
}

// GetCollectionKey

template<typename ChildObjectType, typename ChildTableDefinition, typename ShardType>
const std::string& CollectionShard<ChildObjectType, ChildTableDefinition, ShardType>::GetCollectionKey() const {
    return m_collectionKey;
}

// CreateChildTable

template<typename ChildObjectType, typename ChildTableDefinition, typename ShardType>
bool CollectionShard<ChildObjectType, ChildTableDefinition, ShardType>::CreateChildTable() const {
    auto route = this->m_router->Route(m_parentPath, true);
    if (!route.db || !route.writable) return false;
    return this->m_definition->CreateTable(route.db);
}

// LoadItem

template<typename ChildObjectType, typename ChildTableDefinition, typename ShardType>
bool CollectionShard<ChildObjectType, ChildTableDefinition, ShardType>::LoadItem(ChildObjectType*& outObject) const {
    const_cast<CollectionShard*>(this)->LoadAllChildren();
    outObject = m_children.empty() ? nullptr : m_children.front().get();
    return true;
}

// SaveItem

template<typename ChildObjectType, typename ChildTableDefinition, typename ShardType>
bool CollectionShard<ChildObjectType, ChildTableDefinition, ShardType>::SaveItem(const ChildObjectType* object) const {
    const_cast<CollectionShard*>(this)->SaveAllChildren();
    return true;
}

