
#pragma once
#include "CommandRegistry.h"
#include "CommandClasses.h"
#include "UniverseCommands.hpp"
#include "CommandExample.hpp"
#include "Commands/SystemCommandModule.h"

#include "CommandExample.hpp" //Registers Example Command.
#include <json.hpp>


using json = nlohmann::json;


class NavigateCommandModule : public CommandModule {
public:
    NavigateCommandModule() = default;
    
    std::vector<CommandDef> getCommands() override {
        return {
            CommandDef{
                json::parse(R"({
                    "name": "nav",
                    "aliases": [],
                    "category": "navigation",
                    "description": "navigate to different domains"
                })"),
                [](const CommandContext& ctx) -> CommandResult {
                    return Execute_Navigate(ctx);
                },
                {}
            },
            CommandDef{
                json::parse(R"({
                    "name": "test",
                    "aliases": [],
                    "category": "test",
                    "description": "Test command. For things that need testing"
                })"),
                [](const CommandContext& ctx) -> CommandResult {
                    return Execute_Test(ctx);
                },
                {}
            }
        };
    }

        static CommandResult Execute_Navigate(const CommandContext& ctx);
        static CommandResult Execute_Test(const CommandContext& ctx)
        {
            json exampleScheme = {
                {"tableName", "characters"},
                {"scheme", {
                    {"rows", 5},
                    {"cols", 4},
                    {"data", {
                        json::array({"Name", "Level", "Class", "HP"}),
                        json::array({"Legolas", "18", "Archer", "85"}),
                        json::array({"Gimli", "19", "Dwarf", "120"}),
                        json::array({"Frodo", "15", "Hobbit", "40"})
                    }}
                }},
                {"path", "campaign/party/members"},
                {"onClose", "table-editor-1717593600"}
            };

            json state;
            state["request-open-table"] = exampleScheme; //EVENT NAME === Name of subState

            return {"Open Table Editor!", {"request-open-table"}, state};
        };
};

class CommandBundle {
public:
    enum CommandDomain{
        CR_Global,
        CR_System,
        CR_Universe,
        CR_World,
        CR_Region,
        CR_Place,
        CR_Character,
        CR_Object,
        CR_Item
    };

    CommandBundle() {
        CRSystem = std::make_shared<CommandRegistry>();

        CRUniverse = std::make_shared<CommandRegistry>();
        CRWorld = std::make_shared<CommandRegistry>();        
        CRRegion = std::make_shared<CommandRegistry>();  
        CRPlace = std::make_shared<CommandRegistry>();  
        
        CRCharacter = std::make_shared<CommandRegistry>();        
        CRObject = std::make_shared<CommandRegistry>();        
        CRItem = std::make_shared<CommandRegistry>();
    }

    CommandRegistry* GetCRSystem() {if(CRSystem){return CRSystem.get();}return nullptr;}

    CommandRegistry* GetCRUniverse() {if(CRUniverse){return CRUniverse.get();}return nullptr;}
    CommandRegistry* GetCRWorld() {if(CRWorld) {return CRWorld.get();} return nullptr;}
    CommandRegistry* GetCRRegion() {if(CRRegion) {return CRRegion.get();} return nullptr;}
    CommandRegistry* GetCRPlace() {if(CRPlace) {return CRPlace.get();} return nullptr;}

    CommandRegistry* GetCRCharacter() {if(CRCharacter) {return CRCharacter.get();} return nullptr;}
    CommandRegistry* GetCRObject() {if(CRObject) {return CRObject.get();} return nullptr;}
    CommandRegistry* GetCRItem() {if(CRItem) {return CRItem.get();} return nullptr;}

    void registerModuleForDomain(CommandDomain domain, std::shared_ptr<CommandModule> module) {
        std::string domainName = getDomainName(domain);
        DomainCommandRegistry::registerModuleForDomain(domainName, module);
        CommandRegistry* registry = getRegistry(domain);
        if (registry) registry->registerCommands(module->getCommands());
    }
    //Final Injection. Actually Register bundled commands. 
    void InjectCommands()
    {
        GlobalCommandRegistry::InjectInto(CRSystem.get());
        DomainCommandRegistry::injectIntoDomain("system", CRSystem.get());

        GlobalCommandRegistry::InjectInto(CRUniverse.get());
        DomainCommandRegistry::injectIntoDomain("universe", CRUniverse.get());
        
        GlobalCommandRegistry::InjectInto(CRWorld.get());
        DomainCommandRegistry::injectIntoDomain("world", CRWorld.get());
        
        GlobalCommandRegistry::InjectInto(CRCharacter.get());
        DomainCommandRegistry::injectIntoDomain("character", CRCharacter.get());
        
        GlobalCommandRegistry::InjectInto(CRObject.get());
        DomainCommandRegistry::injectIntoDomain("object", CRObject.get());
        
        GlobalCommandRegistry::InjectInto(CRItem.get());
        DomainCommandRegistry::injectIntoDomain("item", CRItem.get());
    };

public:
    CommandResult executeCommand(CommandDomain domain, const std::vector<std::string>& args, std::map<std::string, std::string>& state) {
        

        if (domain == CR_Global) {
            return GlobalCommandRegistry::Execute(args, state);
        }
        CommandRegistry* registry = getRegistry(domain);
        
        if (!registry) return {"invalid domain\n", {}, {}};
        return registry->execute(args, state, getDomainName(domain));
    }

private:
    std::shared_ptr<CommandRegistry> CRSystem;

    std::shared_ptr<CommandRegistry> CRUniverse;
    std::shared_ptr<CommandRegistry> CRWorld;
    std::shared_ptr<CommandRegistry> CRRegion;
    std::shared_ptr<CommandRegistry> CRPlace;
    std::shared_ptr<CommandRegistry> CRCharacter;
    std::shared_ptr<CommandRegistry> CRObject;
    std::shared_ptr<CommandRegistry> CRItem;

    CommandRegistry* getRegistry(CommandDomain domain) {
        switch (domain) {
            case CR_System: return GetCRSystem();
            
            case CR_Universe: return GetCRUniverse();
            case CR_World: return GetCRWorld();
            case CR_Region: return GetCRRegion();
            case CR_Place: return GetCRWorld();
            
            case CR_Character: return GetCRCharacter();
            case CR_Object: return GetCRObject();
            case CR_Item: return GetCRItem();
            default: return nullptr;
        }
    }

    std::string getDomainName(CommandDomain domain) {
        switch (domain) {
            case CR_System: return "system";
            
            case CR_Universe: return "universe";
            case CR_World: return "world";
            case CR_Region: return "region";
            case CR_Place: return "place";
            
            case CR_Character: return "character";
            case CR_Object: return "object";
            case CR_Item: return "item";
            default: return "";
        }
    }
};
