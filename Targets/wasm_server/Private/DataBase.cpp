#include "DataBase.h"
#include <iostream>
#include <sstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

DataBase::DataBase() : db(nullptr) {}

DataBase::~DataBase() {
    close();
}

bool DataBase::open(const std::string& dbPath) {
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    
    // Enable foreign keys
    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);
    
    std::cout << "Database opened: " << dbPath << std::endl;
    return true;
}

void DataBase::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

std::string DataBase::query(const std::string& sql) {
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        json error;
        error["error"] = sqlite3_errmsg(db);
        return error.dump();
    }
    
    json results = json::array();
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        json row;
        int colCount = sqlite3_column_count(stmt);
        
        for (int i = 0; i < colCount; i++) {
            std::string colName = sqlite3_column_name(stmt, i);
            int type = sqlite3_column_type(stmt, i);
            
            if (type == SQLITE_NULL) {
                row[colName] = nullptr;
            } else if (type == SQLITE_INTEGER) {
                row[colName] = sqlite3_column_int64(stmt, i);
            } else if (type == SQLITE_FLOAT) {
                row[colName] = sqlite3_column_double(stmt, i);
            } else {
                row[colName] = std::string((const char*)sqlite3_column_text(stmt, i));
            }
        }
        results.push_back(row);
    }
    
    sqlite3_finalize(stmt);
    return results.dump();
}

bool DataBase::execute(const std::string& sql) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

int64_t DataBase::lastInsertId() {
    return sqlite3_last_insert_rowid(db);
}

void DataBase::beginTransaction() {
    execute("BEGIN TRANSACTION;");
}

void DataBase::commit() {
    execute("COMMIT;");
}

void DataBase::rollback() {
    execute("ROLLBACK;");
}

bool DataBase::tableExists(const std::string& tableName) {
    std::string sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='" + tableName + "';";
    std::string result = query(sql);
    json parsed = json::parse(result);
    return !parsed.empty();
}
