// CommandClasses.h
#pragma once
#include "CommandRegistry.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include <vector>
#include <memory>
#include <shared_mutex>



class CommandModule {
public:
    virtual ~CommandModule() = default;
    virtual std::vector<CommandDef> getCommands() = 0;
};



//Dumb registry class. Stores static vector: CommandModule 
class GlobalCommandRegistry {
private:
    static inline std::vector<std::shared_ptr<CommandModule>>& Modules() {
        static std::vector<std::shared_ptr<CommandModule>> mods;
        return mods;
    }

    static inline std::shared_mutex& ModulesLock() {
        static std::shared_mutex lk;
        return lk;
    }

public:
    static inline void RegisterModule(std::shared_ptr<CommandModule> module) {
        std::unique_lock lk(ModulesLock());
        Modules().push_back(module);
    }
    static inline void InjectInto(CommandRegistry* registry) {
        std::shared_lock lk(ModulesLock());
        for (auto& module : Modules()) {
            registry->registerCommands(module->getCommands());
        }
    }
static inline CommandResult Execute(const std::vector<std::string>& args, 
                                 std::map<std::string, std::string>& state) {
    std::shared_lock lk(ModulesLock());
    if (args.empty()) return {"no command\n", {}, {}};
                                
    std::string cmdName = args[0];
                                
    // Handle help command
    if (cmdName == "help" || cmdName == "?") {
        if (args.size() == 1) {
            // List all available commands
            std::string output = "Available commands:\n";
            for (auto& module : Modules()) {
                auto cmds = module->getCommands();
                for (auto& cmd : cmds) {
                    output += "  " + std::string(cmd.meta["name"]) + "\n";
                }
            }
            return {output, {}, {}};
        } else {
            // Show command description
            std::string targetCmd = args[1];
            for (auto& module : Modules()) {
                auto cmds = module->getCommands();
                for (auto& cmd : cmds) {
                    if (cmd.meta["name"] == targetCmd) {
                        if (cmd.meta.contains("description")) {
                            return {std::string(cmd.meta["description"]) + "\n", {}, {}};
                        }
                        return {"no description available\n", {}, {}};
                    }
                }
            }
            return {"command not found: " + targetCmd + "\n", {}, {}};
        }
    }
    
    // Execute regular command
    for (auto& module : Modules()) {
        auto cmds = module->getCommands();
        for (auto& cmd : cmds) {
            if (cmd.meta["name"] == cmdName) {
                CommandContext ctx{std::vector<std::string>(args.begin() + 1, args.end()), "global", state};
                return cmd.solver(ctx);
            }
        }
    }
    return {"command not found: " + args[0] + "\n", {}, {}};
}


};



//Dumb registry class. Stores static vector: CommandModule 
class DomainCommandRegistry {
private:
    static inline DomainCommandRegistry& instance() {
        static DomainCommandRegistry inst;
        return inst;
    }

    mutable std::shared_mutex lock;
    std::unordered_map<std::string, std::vector<std::shared_ptr<CommandModule>>> domainModules;

    DomainCommandRegistry() = default;

public:
    static inline void registerModuleForDomain(const std::string& domain,
                                       std::shared_ptr<CommandModule> module) {
        std::unique_lock lk(instance().lock);
        instance().domainModules[domain].push_back(module);
    }

    static inline void injectIntoDomain(const std::string& domain, CommandRegistry* registry) {
        std::shared_lock lk(instance().lock);
        GlobalCommandRegistry::InjectInto(registry);
        
        auto it = instance().domainModules.find(domain);
        if (it != instance().domainModules.end()) {
            for (auto& module : it->second) {
                registry->registerCommands(module->getCommands());
            }
        }
    }
};
