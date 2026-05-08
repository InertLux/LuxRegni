#include "lux_regni.h"
#include "../core/world.h"
#include "../persistence/database.h"

// Global state (singleton pattern)
static World* g_world = nullptr;
static Database* g_database = nullptr;

extern "C" {
    int32_t InitBackend() {
        if (g_world) return 0;  // Already initialized
        g_world = new World();
        g_database = new Database("./gamedata.db");
        
        if (!g_database->Connect()) {
            return -1;
        }
        
        g_world->Initialize();
        return 1;  // Success
    }

    void ShutdownBackend() {
        if (g_world) {
            g_world->Shutdown();
            delete g_world;
            g_world = nullptr;
        }
        if (g_database) {
            g_database->Disconnect();
            delete g_database;
            g_database = nullptr;
        }
    }

    void UpdateWorld(float deltaTime) {
        if (g_world) g_world->Update(deltaTime);
    }

    int32_t CreateEntity(const char* jsonData) {
        if (!g_world) return -1;
        // TODO: Parse JSON, create entity
        return 1;
    }

    void DestroyEntity(int32_t entityId) {
        if (!g_world) return;
        g_world->GetEntityManager().Destroy(entityId);
    }
}
