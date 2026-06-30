#pragma once
#include "DataBase.h"
#include <memory>

class DataManager {
private:
    std::unique_ptr<DataBase> db;
    
public:
    DataManager();
    ~DataManager();
    
    void initialize(const std::string& dbPath);
    void shutdown();
    
    // Entity operations
    std::string createEntity(const std::string& type, const std::string& data);
    std::string getEntity(const std::string& id);
    std::string updateEntity(const std::string& id, const std::string& field, const std::string& value);
    std::string deleteEntity(const std::string& id);
    std::string listEntities(const std::string& type);
    
    // Schema
    std::string createType(const std::string& typeName, const std::string& schema);
    std::string listTypes();
    
    std::string getStatus();
};
