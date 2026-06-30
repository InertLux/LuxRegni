// Modules/IDMCore/CommandExample.hpp

#pragma once
#include <CommandRegistry.h>
#include <CommandClasses.h>
#include <memory>
#include <string>




class SystemCommandModule : public CommandModule {
public:
    SystemCommandModule() = default;
    
    std::vector<CommandDef> getCommands() override {
        return {
            CommandDef{

                    //Init Regnum
                json::parse(R"({
                    "name": "initialize",
                    "aliases": ["init", "start"],
                    "category": "Sys-Regnum",
                    "description": "Start a Regnum instance"
                })"),
                [](const CommandContext& ctx) -> CommandResult {
                  return Execute_Init(ctx);
                },
                {}
            },
            CommandDef{

                    //Init Regnum
                json::parse(R"({
                    "name": "shutdown",
                    "aliases": ["close", "quit"],
                    "category": "Sys-Regnum",
                    "description": "Close Regnum"
                })"),
                [](const CommandContext& ctx) -> CommandResult {
                  return Execute_Shutdown(ctx);
                },
                {}
            },

            CommandDef{

                    //Init Regnum
                json::parse(R"({
                    "name": "projects",
                    "aliases": ["ListProj"],
                    "category": "Sys-Regnum",
                    "description": "List all Local Regni Projects"
                })"),
                [](const CommandContext& ctx) -> CommandResult {
                  return Execute_ListProjects(ctx);
                },
                {}
            },
            CommandDef{

                    //Init Regnum
                json::parse(R"({
                    "name": "create",
                    "aliases": [],
                    "category": "Sys-Regnum",
                    "description": "Start a Regnum instance \n Usage: create RegniID"
                })"),
                [](const CommandContext& ctx) -> CommandResult {
                  return Execute_CreateProject(ctx);
                },
                {}
            },
            CommandDef{

                    //Init Regnum
                json::parse(R"({
                    "name": "delete",
                    "aliases": [],
                    "category": "Sys-Regnum",
                    "description": "Delete a Regnum Project \n Usage: delete RegniID RegniID"
                })"),
                [](const CommandContext& ctx) -> CommandResult {
                  return Execute_DeleteProject(ctx);
                },
                {}
            },
            CommandDef{

                    //Init Regnum
                json::parse(R"({
                    "name": "open",
                    "aliases": [],
                    "category": "Sys-Regnum",
                    "description": "Open a Regnum Project \n Usage: open RegniID target ReadOnly = false"
                })"),
                [](const CommandContext& ctx) -> CommandResult {
                  return Execute_OpenProject(ctx);
                },
                {}
            },
            CommandDef{

                    //Init Regnum
                json::parse(R"({
                    "name": "close",
                    "aliases": [],
                    "category": "Sys-Regnum",
                    "description": "Close a Regnum Target \n Usage: close RegniID target save = true"
                })"),
                [](const CommandContext& ctx) -> CommandResult {
                  return Execute_CloseProject(ctx);
                },
                {}
            },
            CommandDef{

                    //Init Regnum
                json::parse(R"({
                    "name": "shard",
                    "aliases": [],
                    "category": "Sys-Regnum",
                    "description": "Create a new shard from a base \n Usage: shard RegniID Base ShardName "
                })"),
                [](const CommandContext& ctx) -> CommandResult {
                  return Execute_NewShard(ctx);
                },
                {}
            },
            CommandDef{

                    //Init Regnum
                json::parse(R"({
                    "name": "new-base",
                    "aliases": [],
                    "category": "Sys-Regnum",
                    "description": "Create a new Base composition. Usage: new-base base, [shards]"
                })"),
                [](const CommandContext& ctx) -> CommandResult {
                  return Execute_NewBase(ctx);
                },
                {}
            }
        };
    }

    static CommandResult Execute_Init(const CommandContext& ctx);
    static CommandResult Execute_Shutdown(const CommandContext& ctx);
    
    static CommandResult Execute_ListProjects(const CommandContext& ctx);
    
    static CommandResult Execute_CreateProject(const CommandContext& ctx);
    static CommandResult Execute_DeleteProject(const CommandContext& ctx);

    static CommandResult Execute_OpenProject(const CommandContext& ctx);
    static CommandResult Execute_CloseProject(const CommandContext& ctx);

    static CommandResult Execute_NewShard(const CommandContext& ctx);
    static CommandResult Execute_NewBase(const CommandContext& ctx);
};