#include "IDMPathRouter.h"
#include "IDMTemplates.hpp"
#include "IDMTypes.h"



  std::string DatabaseRouterImpl::SafeNameFromPath(const std::string& path) {
        std::string safeName = path;
        if (!safeName.empty() && safeName.front() == '/') safeName = safeName.substr(1);
        if (!safeName.empty() && safeName.back() == '/') safeName = safeName.substr(0, safeName.length() - 1);
        std::replace(safeName.begin(), safeName.end(), '/', '_');
        return safeName;
    }
    
      bool DatabaseRouterImpl::MatchesRule(const std::vector<std::string>& pathTokens, const std::vector<std::string>& ruleTokens) {
        if (pathTokens.size() != ruleTokens.size()) return false;
        for (size_t i = 0; i < ruleTokens.size(); ++i) {
            if (ruleTokens[i] != "*" && ruleTokens[i] != pathTokens[i]) return false;
        }
        return true;
    }

     std::vector<std::string> DatabaseRouterImpl::TokenizePath(const std::string& path) {
        std::vector<std::string> tokens;
        size_t start = 0, end = 0;
        while ((end = path.find('/', start)) != std::string::npos) {
            if (end > start) tokens.push_back(path.substr(start, end - start));
            start = end + 1;
        }
        if (start < path.length()) tokens.push_back(path.substr(start));
        return tokens;
    }
    
     uint64_t DatabaseRouterImpl::HashTokens(const std::vector<std::string>& tokens) {
        std::hash<std::string> hasher;
        uint64_t hash = 0;
        for (size_t i = 0; i < tokens.size(); ++i) {
            hash ^= (hasher(tokens[i]) << (i & 7));
        }
        return hash;
    }

     bool DatabaseRouterImpl::InitializeMetadataDatabase() {
        std::string metaPath = m_projectRoot + "/.metadata.db";
        m_metadataDb = GetOrOpenDatabase(metaPath);
        if (!m_metadataDb) return false;
        
        const char* createTableSql = R"(
            CREATE TABLE IF NOT EXISTS TargetMetadata (
                id INTEGER PRIMARY KEY,
                targetName TEXT UNIQUE NOT NULL,
                schemaVersion TEXT NOT NULL,
                createdAt INTEGER NOT NULL,
                lastModified INTEGER NOT NULL
            );
        )";
        
        char* errMsg = nullptr;
        if (sqlite3_exec(m_metadataDb, createTableSql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
            sqlite3_free(errMsg);
            return false;
        }
        return true;
    }


    
    std::vector<IDMRouting::PathSegment> DatabaseRouterImpl::ParsePathTemplate(const std::string& pathSpec) {
        std::vector<IDMRouting::PathSegment> segments;
        size_t start = (pathSpec.front() == '/') ? 1 : 0;
        size_t end = 0;

        while ((end = pathSpec.find('/', start)) != std::string::npos) {
            if (end > start) {
                std::string seg = pathSpec.substr(start, end - start);
                if (seg == "{}") {
                    segments.push_back({IDMRouting::SegmentType::Wildcard, ""});
                } else if (seg == "{@}") {
                    segments.push_back({IDMRouting::SegmentType::ResourceId, ""});
                } else if (seg.front() == '{' && seg.back() == '}') {
                    segments.push_back({IDMRouting::SegmentType::ResourceType, seg.substr(1, seg.length() - 2)});
                } else {
                    segments.push_back({IDMRouting::SegmentType::Literal, seg});
                }
            }
            start = end + 1;
        }
        if (start < pathSpec.length()) {
            std::string seg = pathSpec.substr(start);
            if (seg == "{}") {
                segments.push_back({IDMRouting::SegmentType::Wildcard, ""});
            } else if (seg == "{@}") {
                segments.push_back({IDMRouting::SegmentType::ResourceId, ""});
            } else if (seg.front() == '{' && seg.back() == '}') {
                segments.push_back({IDMRouting::SegmentType::ResourceType, seg.substr(1, seg.length() - 2)});
            } else {
                segments.push_back({IDMRouting::SegmentType::Literal, seg});
            }
        }
        return segments;
    }


    void DatabaseRouterImpl::RegisterRoute(const std::string& pathSpec,
                                        const std::string& database,
                                        const std::string& table,
                                        const IDMTemplates::ColumnDescriptor* cols,
                                        size_t colCount,
                                        bool isCollection) {
        IDMRouting::RouteEntry entry;
        entry.targetDatabase = database;
        entry.targetTable = isCollection ? "" : table;
        entry.isCollection = isCollection;
        entry.columns = cols;
        entry.columnCount = colCount;
        entry.path = DatabaseRouterImpl::ParsePathTemplate(pathSpec);
                                        
        for (int i = 0; i < (int)entry.path.size(); ++i) {
            if (entry.path[i].type == IDMRouting::SegmentType::ResourceId) {
                entry.parentIdTokenIndex = i;
                break;
            }
        }

        IDMRouting::g_rulesOrdered.push_back(entry);
        std::sort(IDMRouting::g_rulesOrdered.begin(), IDMRouting::g_rulesOrdered.end(),
            [](const IDMRouting::RouteEntry& a, const IDMRouting::RouteEntry& b) {
                int aWildcards = std::count_if(a.path.begin(), a.path.end(),
                    [](const IDMRouting::PathSegment& s) { return s.type == IDMRouting::SegmentType::Wildcard; });
                int bWildcards = std::count_if(b.path.begin(), b.path.end(),
                    [](const IDMRouting::PathSegment& s) { return s.type == IDMRouting::SegmentType::Wildcard; });
                if (aWildcards != bWildcards) return aWildcards < bWildcards;
                return a.path.size() > b.path.size();
            });
    }

    std::vector<std::string> DatabaseRouterImpl::ParsePath(const std::string& path) {
        std::vector<std::string> pathTokens;
        std::string cleaned = path;

        if (!cleaned.empty() && cleaned.front() == '/') cleaned = cleaned.substr(1);
        if (!cleaned.empty() && cleaned.back() == '/') cleaned = cleaned.substr(0, cleaned.length() - 1);

        size_t start = 0, end = 0;
        while ((end = cleaned.find('/', start)) != std::string::npos) {
            if (end > start) pathTokens.push_back(cleaned.substr(start, end - start));
            start = end + 1;
        }
        if (start < cleaned.length()) pathTokens.push_back(cleaned.substr(start));
        return pathTokens;
    }
    
    std::string DatabaseRouterImpl::ResolveTableName(const std::string& path) {
        auto pathTokens = ParsePath(path);
        auto result = Route(pathTokens, false);
        if (!result.db) {
            throw std::runtime_error("No route found for path: " + path);
        }
        return result.tableName;
    }


    IDMTemplates::RouteResult DatabaseRouterImpl::Route(const std::string& path, bool isWrite) {
        auto pathTokens = ParsePath(path);
        return Route(pathTokens, isWrite);
    }

    IDMTemplates::RouteResult DatabaseRouterImpl::Route(const std::vector<std::string>& pathTokens, bool isWrite) {
        for (const auto& rule : IDMRouting::g_rulesOrdered) {
            if (pathTokens.size() != rule.path.size()) continue;

            bool matches = true;
            for (size_t i = 0; i < rule.path.size(); ++i) {
                const auto& seg = rule.path[i];
                if (seg.type == IDMRouting::SegmentType::Literal && seg.value != pathTokens[i]) {
                    matches = false;
                    break;
                }
                if (seg.type == IDMRouting::SegmentType::ResourceType && seg.value != pathTokens[i]) {
                    matches = false;
                    break;
                }
            }

            if (matches) {
                std::string dbPath = GetFragmentRootPath(m_currentTarget) + "/" + rule.targetDatabase + ".db";
                sqlite3* db = GetOrOpenDatabase(dbPath);
                std::string resourceId = (rule.parentIdTokenIndex >= 0) ? pathTokens[rule.parentIdTokenIndex] : "";
                std::string dynamicTable = rule.isCollection ? resourceId : rule.targetTable;
                return {db, isWrite, dbPath, resourceId, dynamicTable, rule.isCollection, rule.targetTable};
            }
        }
        return {nullptr, false, "", "", "", false};
    }



    // ##########################################################################################
    // ##########################################################################################

     bool DatabaseRouterImpl::InitializeProject(const std::string& projectPath, const std::string& schemaVersion) {
        m_projectRoot = projectPath;
        m_baseDataPath = m_projectRoot;

        std::cout << "Initializing Project: " << projectPath  << std::endl;
        PlatformEnsureDirectoryExists(m_projectRoot);
        auto RootTargetPath = GetFragmentRootPath(Target::Root);
        PlatformEnsureDirectoryExists(RootTargetPath);
        InitializeMetadataDatabase();

        m_currentTarget = Target::Root;
        if (!RecordTargetMetadata("Root", schemaVersion)) return false;
        return CreateNewTarget(RootTargetPath);

    }

     bool DatabaseRouterImpl::CreateNewBase(const std::string& baseName, const std::string& schemaVersion) {
        if (baseName.empty()) return false;
        m_activeBaseName = baseName;
        m_currentTarget = Target::Base;
        std::string basePath = GetFragmentRootPath(Target::Base);

        PlatformEnsureDirectoryExists(basePath);

        if (!RecordTargetMetadata(baseName, schemaVersion)) return false;
        return CreateNewTarget(basePath);
    }

     bool DatabaseRouterImpl::CreateNewShard(const std::string& shardName, const std::string& schemaVersion) {
        if (shardName.empty() || m_activeBaseName.empty()) return false;
        m_activeShardName = shardName;
        m_currentTarget = Target::Shard;
        std::string basePath = GetFragmentRootPath(Target::Shard);

        PlatformEnsureDirectoryExists(basePath);
        
      

        if (!RecordTargetMetadata(shardName, schemaVersion)) return false;
        return CreateNewTarget(basePath);
    }


    // ##########################################################################################
    // ##########################################################################################
    
    bool DatabaseRouterImpl::RecordTargetMetadata(const std::string& targetName, const std::string& schemaVersion) {
        if (!m_metadataDb) return false;

        int64_t now = std::chrono::system_clock::now().time_since_epoch().count();
        const char* sql = "INSERT OR REPLACE INTO TargetMetadata (targetName, schemaVersion, createdAt, lastModified) VALUES (?, ?, ?, ?)";

        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(m_metadataDb, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;

        sqlite3_bind_text(stmt, 1, targetName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, schemaVersion.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int64(stmt, 3, now);
        sqlite3_bind_int64(stmt, 4, now);

        bool success = sqlite3_step(stmt) == SQLITE_DONE;
        sqlite3_finalize(stmt);
        return success;
    }

    bool DatabaseRouterImpl::UpdateTargetSchemaVersion(const std::string& targetName, const std::string& newVersion) {
        if (!m_metadataDb) return false;

        int64_t now = std::chrono::system_clock::now().time_since_epoch().count();
        const char* sql = "UPDATE TargetMetadata SET schemaVersion = ?, lastModified = ? WHERE targetName = ?";

        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(m_metadataDb, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;

        sqlite3_bind_text(stmt, 1, newVersion.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int64(stmt, 2, now);
        sqlite3_bind_text(stmt, 3, targetName.c_str(), -1, SQLITE_STATIC);

        bool success = sqlite3_step(stmt) == SQLITE_DONE;
        sqlite3_finalize(stmt);
        return success;
    }

    bool DatabaseRouterImpl::GetTargetMetadata(const std::string& targetName, TargetMetadata& outMeta) {
        if (!m_metadataDb) return false;

        const char* sql = "SELECT targetName, schemaVersion, createdAt, lastModified FROM TargetMetadata WHERE targetName = ?";

        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(m_metadataDb, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;

        sqlite3_bind_text(stmt, 1, targetName.c_str(), -1, SQLITE_STATIC);

        bool found = false;
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            outMeta.targetName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            outMeta.schemaVersion = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            outMeta.createdAt = sqlite3_column_int64(stmt, 2);
            outMeta.lastModified = sqlite3_column_int64(stmt, 3);
            found = true;
        }
        sqlite3_finalize(stmt);
        return found;
    }

    bool DatabaseRouterImpl::CreateNewTarget(const std::string& basePath) {
        bool success = true;

        std::cout << "Initializing target: " << basePath << std::endl;

        std::unordered_map<std::string, sqlite3*> dbMap;

        for (const auto& rule : IDMRouting::g_rulesOrdered) {
            std::string dbPath = basePath + "/" + rule.targetDatabase + ".db";

            size_t lastSlash = dbPath.find_last_of('/');
            if (lastSlash != std::string::npos) {
                std::string dirPath = dbPath.substr(0, lastSlash);
                PlatformEnsureDirectoryExists(dirPath);
            }

            sqlite3* db = GetOrOpenDatabase(dbPath);
            if (!db) {
                success = false;
                continue;
            }

            sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);
            sqlite3_exec(db, "PRAGMA journal_mode = WAL;", nullptr, nullptr, nullptr);

            dbMap[rule.targetDatabase] = db;
        }

        for (const auto& rule : IDMRouting::g_rulesOrdered) {
            auto it = dbMap.find(rule.targetDatabase);
            if (it == dbMap.end()) {
                success = false;
                continue;
            }

            sqlite3* db = it->second;
            std::string tableName = rule.targetTable;

            std::cout << "Creating Table: " << tableName << std::endl;

            std::string columnDefs;
            for (size_t i = 0; i < rule.columnCount; ++i) {
                if (i > 0) columnDefs += ", ";
                columnDefs += rule.columns[i].sqlDef;
            }

            std::string createTableSql = "CREATE TABLE IF NOT EXISTS " + tableName + " (" + columnDefs + ")";
            char* errMsg = nullptr;
            if (sqlite3_exec(db, createTableSql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
                std::cerr << "Failed to create table " << tableName << ": " << errMsg << std::endl;
                sqlite3_free(errMsg);
                success = false;
            }
        }

        return success;
    }


     bool DatabaseRouterImpl::AuditTarget(const std::string& basePath, 
                             const std::function<bool(sqlite3*, const IDMRouting::RouteEntry&)>& auditFn) {
        bool success = true;
                            
        for (const auto& rule : IDMRouting::g_rulesOrdered) {
            std::string dbPath = GetFragmentRootPath(m_currentTarget) + "/" + rule.targetDatabase + ".db";
            sqlite3* db = GetOrOpenDatabase(dbPath);
            if (db && !auditFn(db, rule)) {
                success = false;
            }
        }

        return success;
    }


    IDMTemplates::RouteResult DatabaseRouterImpl::ResolveRoute(const IDMRouting::RouteEntry& rule, 
                            const std::vector<std::string>& pathTokens, 
                            bool isWrite) {
        std::string dbPath = GetFragmentRootPath(m_currentTarget) + "/" + rule.targetDatabase + ".db";
        
        std::cout << "Resolving DB at " << dbPath << std::endl;
        sqlite3* db = GetOrOpenDatabase(dbPath);
        if(!db)
        {
            std::cout << "DB invalid"<< std::endl;
        }   
        else
        {
            std::cout << "DB Good"<< std::endl;
        }                     

        std::string parentId = (rule.parentIdTokenIndex >= 0 && rule.parentIdTokenIndex < (int)pathTokens.size()) 
            ? pathTokens[rule.parentIdTokenIndex] 
            : "";

        std::string dynamicTable = rule.isCollection ? parentId : rule.targetTable;


        IDMTemplates::RouteResult RouteResult{db, isWrite, dbPath, parentId, dynamicTable, rule.isCollection};
        RouteResult.tableName = rule.targetTable; 
        return RouteResult;
    }
    
    sqlite3* DatabaseRouterImpl::GetOrOpenDatabase(const std::string& dbPath) {
        auto it = m_dbCache.find(dbPath);
        if (it != m_dbCache.end()) return it->second;
        sqlite3* db = PlatformOpenDatabase(dbPath);
        m_dbCache[dbPath] = db;
        return db;
    }
    
    std::string DatabaseRouterImpl::GetFragmentRootPath(Target target)
    {
        
        switch (target) {
            case Target::Root:
                return m_baseDataPath + "/Root";
            case Target::Base:
                return m_baseDataPath + "/" + m_activeBaseName;
            case Target::Shard:
                return m_baseDataPath + "/" + m_activeBaseName + "/Shards/" + m_activeShardName;
            default:
                return m_baseDataPath;
        }
    };