#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

// ============================================================================
// Stub implementations (POC only) - DEFINE BEFORE Program CLASS
// ============================================================================

class TableSchemaManager {
public:
    bool Initialize() {
        std::cout << "[TableSchemaManager] Initialized" << std::endl;
        return true;
    }

    std::string CreateType(const std::string& type_name, const std::string& fields_json) {
        std::string type_id = "type_" + type_name + "_" + std::to_string(types_.size());
        types_[type_id] = {
            {"name", type_name},
            {"fields", fields_json}
        };
        std::cout << "[TableSchemaManager::CreateType] Created type: " << type_id << std::endl;
        return type_id;
    }

    std::string CreateSubtype(const std::string& type_id,
                             const std::string& subtype_name,
                             const std::string& fields_json,
                             bool is_optional) {
        std::string subtype_id = type_id + "_" + subtype_name;
        subtypes_[subtype_id] = {
            {"name", subtype_name},
            {"fields", fields_json},
            {"optional", is_optional ? "true" : "false"}
        };
        std::cout << "[TableSchemaManager::CreateSubtype] Created subtype: " << subtype_id << std::endl;
        return subtype_id;
    }

    std::string GetTypesAsJson() {
        return "[]";
    }

    std::string GetTypeAsJson(const std::string& type_id) {
        return "{}";
    }

    std::string ListTypeNamesAsJson() {
        std::string result = "[";
        bool first = true;
        for (const auto& pair : types_) {
            if (!first) result += ",";
            result += "\"" + pair.second.at("name") + "\"";
            first = false;
        }
        result += "]";
        return result;
    }

    size_t GetTypeCount() const {
        return types_.size();
    }

private:
    std::map<std::string, std::map<std::string, std::string>> types_;
    std::map<std::string, std::map<std::string, std::string>> subtypes_;
};

class GameMemory {
public:
    bool Initialize(TableSchemaManager* schema_manager) {
        schema_manager_ = schema_manager;
        std::cout << "[GameMemory] Initialized" << std::endl;
        return true;
    }

    std::string CreateEntity(const std::string& type_name,
                            const std::string& subtype_name,
                            const std::string& data_json) {
        std::string entity_id = "entity_" + std::to_string(entities_.size());
        entities_[entity_id] = {
            {"type", type_name},
            {"subtype", subtype_name},
            {"data", data_json}
        };
        std::cout << "[GameMemory::CreateEntity] Created entity: " << entity_id << std::endl;
        return entity_id;
    }

    std::string GetEntityAsJson(const std::string& entity_id) {
        if (entities_.find(entity_id) != entities_.end()) {
            return entities_[entity_id].at("data");
        }
        return "{}";
    }

    bool UpdateEntity(const std::string& entity_id,
                     const std::string& field_path,
                     const std::string& value_json) {
        if (entities_.find(entity_id) == entities_.end()) {
            std::cerr << "[GameMemory::UpdateEntity] Entity not found: " << entity_id << std::endl;
            return false;
        }
        std::cout << "[GameMemory::UpdateEntity] Updated " << entity_id 
                  << " at " << field_path << std::endl;
        return true;
    }

    std::string GetEntitiesByTypeAsJson(const std::string& type_name) {
        std::string result = "[";
        bool first = true;
        for (const auto& pair : entities_) {
            if (pair.second.at("type") == type_name) {
                if (!first) result += ",";
                result += "\"" + pair.first + "\"";
                first = false;
            }
        }
        result += "]";
        return result;
    }

    size_t GetEntityCount() const {
        return entities_.size();
    }

private:
    TableSchemaManager* schema_manager_;
    std::map<std::string, std::map<std::string, std::string>> entities_;
};

// ============================================================================
// Program Class (now TableSchemaManager and GameMemory are complete)
// ============================================================================

class Program {
public:
    Program() 
        : schema_manager_(nullptr), game_memory_(nullptr) {
        std::cout << "[Program] Initialized" << std::endl;
    }

    ~Program() {
        Shutdown();
    }

    bool Initialize() {
        std::cout << "[Program] Initializing server..." << std::endl;
        
        schema_manager_ = std::make_unique<TableSchemaManager>();
        if (!schema_manager_->Initialize()) {
            std::cerr << "[Program] Failed to initialize schema manager" << std::endl;
            return false;
        }

        game_memory_ = std::make_unique<GameMemory>();
        if (!game_memory_->Initialize(schema_manager_.get())) {
            std::cerr << "[Program] Failed to initialize game memory" << std::endl;
            return false;
        }

        std::cout << "[Program] Server initialized successfully" << std::endl;
        return true;
    }

    void Shutdown() {
        std::cout << "[Program] Shutting down..." << std::endl;
        game_memory_.reset();
        schema_manager_.reset();
    }

    std::string CreateType(const std::string& type_name, const std::string& fields_json) {
        if (!schema_manager_) return "";
        return schema_manager_->CreateType(type_name, fields_json);
    }

    std::string CreateSubtype(const std::string& type_id, 
                             const std::string& subtype_name,
                             const std::string& fields_json,
                             bool is_optional) {
        if (!schema_manager_) return "";
        return schema_manager_->CreateSubtype(type_id, subtype_name, fields_json, is_optional);
    }

    std::string GetAllTypes() {
        if (!schema_manager_) return "[]";
        return schema_manager_->GetTypesAsJson();
    }

    std::string GetType(const std::string& type_id) {
        if (!schema_manager_) return "{}";
        return schema_manager_->GetTypeAsJson(type_id);
    }

    std::string CreateEntity(const std::string& type_name,
                            const std::string& subtype_name,
                            const std::string& data_json) {
        if (!game_memory_) return "";
        return game_memory_->CreateEntity(type_name, subtype_name, data_json);
    }

    std::string GetEntity(const std::string& entity_id) {
        if (!game_memory_) return "{}";
        return game_memory_->GetEntityAsJson(entity_id);
    }

    bool UpdateEntity(const std::string& entity_id,
                     const std::string& field_path,
                     const std::string& value_json) {
        if (!game_memory_) return false;
        return game_memory_->UpdateEntity(entity_id, field_path, value_json);
    }

    std::string GetEntitiesByType(const std::string& type_name) {
        if (!game_memory_) return "[]";
        return game_memory_->GetEntitiesByTypeAsJson(type_name);
    }

    std::string ListTypes() {
        if (!schema_manager_) return "[]";
        return schema_manager_->ListTypeNamesAsJson();
    }

    std::string GetStatus() {
        std::string status = R"({
            "status": "running",
            "initialized": true,
            "types_count": )";
        
        if (schema_manager_) {
            status += std::to_string(schema_manager_->GetTypeCount());
        } else {
            status += "0";
        }
        
        status += R"(,
            "entities_count": )";
        
        if (game_memory_) {
            status += std::to_string(game_memory_->GetEntityCount());
        } else {
            status += "0";
        }
        
        status += R"(
        })";
        return status;
    }

private:
    std::unique_ptr<TableSchemaManager> schema_manager_;
    std::unique_ptr<GameMemory> game_memory_;
};

// ============================================================================
// Emscripten JS Bindings
// ============================================================================

EMSCRIPTEN_BINDINGS(luxregni_wasm_server) {
    emscripten::class_<Program>("Program")
        .constructor<>()
        .function("initialize", &Program::Initialize)
        .function("shutdown", &Program::Shutdown)
        .function("createType", &Program::CreateType)
        .function("createSubtype", &Program::CreateSubtype)
        .function("getAllTypes", &Program::GetAllTypes)
        .function("getType", &Program::GetType)
        .function("createEntity", &Program::CreateEntity)
        .function("getEntity", &Program::GetEntity)
        .function("updateEntity", &Program::UpdateEntity)
        .function("getEntitiesByType", &Program::GetEntitiesByType)
        .function("listTypes", &Program::ListTypes)
        .function("getStatus", &Program::GetStatus);
}

// ============================================================================
// Main entry point
// ============================================================================

int main() {
    std::cout << "[LuxRegni WASM Server] Starting..." << std::endl;
    
    static Program program;
    program.Initialize();

    std::cout << "[LuxRegni WASM Server] Ready for JS calls" << std::endl;
    
    return 0;
}
