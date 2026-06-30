#pragma once
#include <sqlite3.h>
#include <string>
#include <vector>
#include <memory>

class DataBase {
private:
    sqlite3* db;
    
public:
    DataBase();
    ~DataBase();
    
    bool open(const std::string& dbPath);
    void close();
    
    // Core operations
    std::string query(const std::string& sql);
    bool execute(const std::string& sql);
    int64_t lastInsertId();
    
    // Transactions
    void beginTransaction();
    void commit();
    void rollback();
    
    // Helpers
    bool tableExists(const std::string& tableName);
};
