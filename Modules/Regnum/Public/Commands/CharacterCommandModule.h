
#pragma once
#include <CommandRegistry.h>
#include <CommandClasses.h>
#include <memory>
#include <string>


/*
    List
    Create
    Delete
    Edit

*/

class CharacterCommandModule : public CommandModule {
public:
    CharacterCommandModule() = default;
    
    std::vector<CommandDef> getCommands() override {
        return {

            CommandDef{
                //List All Cahracters
                json::parse(R"({
                    "name": "list",
                    "aliases": [],
                    "category": "Info",
                    "description": "List all characters in database"
                })"),
                [](const CommandContext& ctx) -> CommandResult {
                  return Execute_List(ctx);
                },
                {}
            },
            CommandDef{
                //Create Character
                json::parse(R"({
                    "name": "create",
                    "aliases": [],
                    "category": "Author",
                    "description": "Create a new character. Add entry to archive."
                })"),
                [](const CommandContext& ctx) -> CommandResult {
                  return Execute_Edit(ctx);
                },
                {}
            },

            CommandDef{
                // Delete Character
                json::parse(R"({
                    "name": "delete",
                    "aliases": [],
                    "category": "Author",
                    "description": "Delete a character from archive. Permanently"
                })"),
                [](const CommandContext& ctx) -> CommandResult {
                  return Execute_Delete(ctx);
                },
                {}
            }
        };
    }

    static CommandResult Execute_List(const CommandContext& ctx);
    static CommandResult Execute_Edit(const CommandContext& ctx);
    static CommandResult Execute_Delete(const CommandContext& ctx);

};