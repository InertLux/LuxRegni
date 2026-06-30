// main.cpp
#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>

#include <IDMTemplates.hpp>
#include <IDMCore.h>
#include <IDMPathRouter.h>

#include <Character.h>

#include "CommandRegistry.h"
#include "Commands.h"
#include "Regnum.h"
#include <AsciiScene.h>
#include <Editors/AsciiTableEditor.h>

#include <json.hpp>


using json = nlohmann::json;

class SceneManager {
private:
    static std::unique_ptr<AsciiScene> active_scene;
    
public:
    static void spawnTableEditor(const json& tableScheme, std::function<void(const json&)> onClose) {
        active_scene = std::make_unique<AsciiTableEditor>(
            tableScheme.value("rows", 5),
            tableScheme.value("cols", 4)
        );
        
        auto editor = static_cast<AsciiTableEditor*>(active_scene.get());
        
        if (tableScheme.contains("data")) {
            for (size_t i = 0; i < tableScheme["data"].size(); ++i) {
                std::vector<std::string> row;
                for (const auto& cell : tableScheme["data"][i]) {
                    row.push_back(cell.get<std::string>());
                }
                editor->setRowData(i, row);
            }
        }
        
        editor->run();
        
        auto [row, col] = editor->getSelectedCell();
        json result = {
            {"selected_row", row},
            {"selected_col", col},
            {"selected_value", editor->getCell(row, col)}
        };
        
        onClose(result);
        active_scene.reset();
    }
};

std::unique_ptr<AsciiScene> SceneManager::active_scene = nullptr;



class UnixDatabaseRouter : public DatabaseRouterImpl {
    private:
    std::unordered_map<std::string, sqlite3*> m_openDatabases;
    std::string m_baseDataPath;

    public:
    UnixDatabaseRouter(const std::string& baseDataPath = "/var/lib/luxregni")
        : m_baseDataPath(baseDataPath) {
        PlatformEnsureDirectoryExists(m_baseDataPath);
    }

    ~UnixDatabaseRouter() override {
        CloseAllDatabases();
    }

    void PlatformEnsureDirectoryExists(const std::string& dirPath) override {
        std::filesystem::create_directories(dirPath);
    }

    sqlite3* PlatformOpenDatabase(const std::string& filePath) override {
        size_t lastSlash = filePath.find_last_of('/');
        if (lastSlash != std::string::npos) {
            std::string dirPath = filePath.substr(0, lastSlash);
            PlatformEnsureDirectoryExists(dirPath);
        std::cout << "Creating/Opening Database: " << filePath << std::endl;
        sqlite3* db = nullptr;
        int rc = sqlite3_open_v2(filePath.c_str(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);
        if (rc != SQLITE_OK) {
            std::string error = db ? sqlite3_errmsg(db) : "unknown error";
            if (db) sqlite3_close(db);
            throw std::runtime_error("Failed to open database: " + filePath + " - " + error);
        }

        sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);
        sqlite3_exec(db, "PRAGMA journal_mode = WAL;", nullptr, nullptr, nullptr);

        return db;
        }
        return nullptr;
    }



    void CloseAllDatabases() override {
        for (auto& [path, db] : m_openDatabases) {
            if (db) sqlite3_close(db);
        }
        m_openDatabases.clear();
    }
};






std::vector<std::string> parseArgs(const std::string& input) {
    std::vector<std::string> args;
    std::istringstream iss(input);
    std::string token;
    while (iss >> token) {
        args.push_back(token);
    }
    return args;
};

namespace RegAsciiEvents{
    static void Handle_RequestOpenTable(json state) {

        static json debugState = {
            {"rows", 5},
            {"cols", 4},
            {"data", {
                json::array({"Name", "Level", "Class", "HP"}),
                json::array({"Legolas", "18", "Archer", "85"})
            }}
        };



        std::string tableName = state.contains("tableName") && state["tableName"].is_string() 
            ? state["tableName"].get<std::string>() 
            : "";
        json scheme = state.contains("scheme") && state["scheme"].is_object() 
            ? state["scheme"] 
            : debugState;
        std::string path = state.contains("path") && state["path"].is_string() 
            ? state["path"].get<std::string>() 
            : "";

        SceneManager::spawnTableEditor(scheme, [tableName, path](const json& result) {
            Regnum::Get()->ImportObjectAsJson(path, result);
        });
    }

    
}

int main() {

    Regnum::Init(std::make_shared<::UnixDatabaseRouter>("/home/user/Regnum"));
    Regnum::Register();
    auto DatabaseRouterInst = Regnum::GetRouter();
    auto RegnumInst = Regnum::Get();
    Regnum::CreateDataBase("/home/user/Regnum");

    // Create debug characters
    Character archer(DatabaseRouterInst, "/Base/Character/Legolas/Character");
    archer.LoadAll();
    std::cout << "Archer: " << archer.GetCharacterData().Name << std::endl;
    archer.SaveAll();

    Character mage(DatabaseRouterInst, "/Base/Character/Gandalf/Character");
    mage.GetCharacterData().Name = "Gandalf";
    mage.LoadAll();
    mage.SaveAll();

    Character warrior(DatabaseRouterInst, "/Base/Character/Aragorn/Character");
    warrior.GetCharacterData().Name = "Gandalf";
    warrior.LoadAll();
    warrior.SaveAll();

    std::cout << "Characters persisted to /home/user/Regnum" << std::endl;

    std::map<std::string, std::string> state;
    std::string input;
    
    while (true) {
        std::cout << RegnumInst->GetCLIPromptText();
        std::getline(std::cin, input);
        if (input == "exit") break;
        if (input.empty()) continue;

        auto args = parseArgs(input);
        if (args.empty()) continue;

        auto result = RegnumInst->executeCommand(args, state);
        std::cout << result.text;
        
        for (const auto& event : result.events) {
            if(event == "request-open-table")
            {
                RegAsciiEvents::Handle_RequestOpenTable(result.state["request-open-table"]);
                continue;
            }
            std::cout << "[Event] " << event << "\n";
        }
    }

    return 0;
};

