#pragma once

// ============  ============

template<typename ObjectType, const TableMetadata* Meta, typename... Properties>
std::string DataTypeImpl<ObjectType, Meta, Properties...>::BuildColumnDefs() {
    std::string result;
    for (size_t i = 0; i < Meta->ColumnCount; ++i) {
        if (i > 0) result += ", ";
        result += Meta->Columns[i].sqlDef;
    }
    return result;
}

template<typename ObjectType, const TableMetadata* Meta, typename... Properties>
template<typename Prop>
void DataTypeImpl<ObjectType, Meta, Properties...>::ExtractAndBind(
    ObjectType* obj, sqlite3_stmt* stmt) const {
    using ValueType = typename Prop::Type;
    ValueType value = IDMConversions::ExtractColumnValue<ValueType>(stmt, Prop::Index);
    auto& member = obj->*Prop::Member;
    member = value;
}

template<typename ObjectType, const TableMetadata* Meta, typename... Properties>
template<typename... Props, size_t... Is>
void DataTypeImpl<ObjectType, Meta, Properties...>::BindColumnsToObjectImpl(
    ObjectType* obj, sqlite3_stmt* stmt, 
    IDMConversions::IndexSequence<Is...>) const {
    (ExtractAndBind<std::tuple_element_t<Is, std::tuple<Properties...>>>(obj, stmt), ...);
}

template<typename ObjectType, const TableMetadata* Meta, typename... Properties>
template<typename Prop>
void DataTypeImpl<ObjectType, Meta, Properties...>::BindMemberValue(
    const ObjectType* obj, sqlite3_stmt* stmt) const {
    using ValueType = typename Prop::Type;
    const auto& value = obj->*Prop::Member;
    IDMConversions::BindValue<ValueType>(stmt, Prop::Index + 1, value);
}

template<typename ObjectType, const TableMetadata* Meta, typename... Properties>
template<typename... Props, size_t... Is>
void DataTypeImpl<ObjectType, Meta, Properties...>::BindMembersToStatementImpl(
    const ObjectType* obj, sqlite3_stmt* stmt,
    IDMConversions::IndexSequence<Is...>) const {
    (BindMemberValue<std::tuple_element_t<Is, std::tuple<Properties...>>>(obj, stmt), ...);
}


// ============ SAVE AND LOAD ============

template<typename ObjectType, const TableMetadata* Meta, typename... Properties>
bool DataTypeImpl<ObjectType, Meta, Properties...>::LoadImpl(
    sqlite3* db, const std::string& tableName, 
    const std::string& whereClause, ObjectType* obj) const {
    std::string query = "SELECT * FROM " + tableName + " WHERE " + whereClause + " LIMIT 1";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) return false;
    
    bool success = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        BindColumnsToObjectImpl(obj, stmt, IDMConversions::make_index_sequence<PropertyCount>{});
        success = true;
    }
    sqlite3_finalize(stmt);
    return success;
}

template<typename ObjectType, const TableMetadata* Meta, typename... Properties>
bool DataTypeImpl<ObjectType, Meta, Properties...>::CreateTable(sqlite3* db, const std::string& tableName) const {
    std::string query = "CREATE TABLE IF NOT EXISTS " + tableName + " (" + BuildColumnDefs() + ")";
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

template<typename ObjectType, const TableMetadata* Meta, typename... Properties>
bool DataTypeImpl<ObjectType, Meta, Properties...>::Load(sqlite3* db, const std::string& tableName, const std::string& whereClause, void* targetObject) const {
    return LoadImpl(db, tableName, whereClause, static_cast<ObjectType*>(targetObject));
}

template<typename ObjectType, const TableMetadata* Meta, typename... Properties>
bool DataTypeImpl<ObjectType, Meta, Properties...>::Save(sqlite3* db, const std::string& tableName, const void* object) const {
    return SaveImpl(db, tableName, static_cast<const ObjectType*>(object));
}
template<typename ObjectType, const TableMetadata* Meta, typename... Properties>
bool DataTypeImpl<ObjectType, Meta, Properties...>::Delete(sqlite3* db, const std::string& tableName, const void* object) const {
    return DeleteImpl(db, tableName, static_cast<const ObjectType*>(object));
}

template<typename ObjectType, const TableMetadata* Meta, typename... Properties>
bool DataTypeImpl<ObjectType, Meta, Properties...>::DeleteImpl(
    sqlite3* db, const std::string& tableName, const ObjectType* obj) const {
    // Assumes first property is the primary key
    using FirstProp = std::tuple_element_t<0, std::tuple<Properties...>>;
    using KeyType = typename FirstProp::Type;
    const auto& keyValue = obj->*FirstProp::Member;
    
    std::string query = "DELETE FROM " + tableName + " WHERE " + 
                        std::string(Meta->Columns[0].name) + " = ?";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) return false;
    
    IDMConversions::BindValue<KeyType>(stmt, 1, keyValue);
    
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

template<typename ObjectType, const TableMetadata* Meta, typename... Properties>
bool DataTypeImpl<ObjectType, Meta, Properties...>::SaveImpl(
    sqlite3* db, const std::string& tableName, const ObjectType* obj) const {
    std::string query = "INSERT OR REPLACE INTO " + tableName + " VALUES (";
    for (size_t i = 0; i < PropertyCount; ++i) {
        if (i > 0) query += ", ";
        query += "?";
    }
    query += ")";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) return false;
    
    BindMembersToStatementImpl(obj, stmt, IDMConversions::make_index_sequence<PropertyCount>{});
    
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}



// ============ METADATA ACCESSORS ============
template<typename ObjectType, const TableMetadata* Meta, typename... Properties>
DataTypeImpl<ObjectType, Meta, Properties...>::DataTypeImpl() {}

template<typename ObjectType, const TableMetadata* Meta, typename... Properties>
DataTypeImpl<ObjectType, Meta, Properties...>::~DataTypeImpl() {}

template<typename ObjectType, const TableMetadata* Meta, typename... Properties>
const char* DataTypeImpl<ObjectType, Meta, Properties...>::GetStaticTableName() const {
    return Meta->Route->TableName.data();
}