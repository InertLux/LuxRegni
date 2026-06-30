// Modules/Universe/UniverseCommands.hpp
#pragma once
#include "CommandRegistry.h"
#include "CommandClasses.h"
#include <memory>




class UniverseCommandModule : public CommandModule {
private:
  
public:
    UniverseCommandModule() {}
    
    std::vector<CommandDef> getCommands() override {
        return {
            CommandDef{
                json::parse(R"({
                    "name": "universe",
                    "aliases": ["u"],
                    "category": "domain",
                    "description": "universe operations"
                })"),
                [this](const CommandContext& ctx) -> CommandResult {
                    return {"dsfg",{},{}};
                },
                {}
            }
        };
    }
};