#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <memory>
#include <functional>
#include <mutex>
#include <shared_mutex>
#include <json.hpp>

using json = nlohmann::json;

struct CommandResult {
    std::string text;
    std::vector<std::string> events;
    json state;
};

struct CommandContext {
    std::vector<std::string> args;
    std::string environment;
    json state;
};

using CommandSolver = std::function<CommandResult(const CommandContext&)>;

struct CommandDef {
    json meta;
    CommandSolver solver;
    std::unordered_map<std::string, CommandDef> methods;
};

class CommandRegistry {
private:
    mutable std::shared_mutex lock;
    std::unordered_map<std::string, CommandDef> commands;
    std::unordered_map<std::string, std::string> aliases;

    inline std::string resolveAlias(const std::string& name) const {
        if(aliases.empty()){return "";}
        auto it = aliases.find(name);
        return (it != aliases.end()) ? it->second : name;
    }

    inline std::string resolveMethodAlias(const std::string& name, const CommandDef& cmd) const {
        auto it = cmd.methods.find(name);
        if (it != cmd.methods.end()) return name;
        
        for (const auto& pair : cmd.methods) {
            if (pair.second.meta.contains("aliases")) {
                for (const auto& alias : pair.second.meta["aliases"]) {
                    if (alias == name) return pair.first;
                }
            }
        }
        return name;
    }

public:
    CommandRegistry() = default;
    ~CommandRegistry() = default;

    inline void registerCommand(const CommandDef& def) {
        std::unique_lock<std::shared_mutex> lk(lock);
        std::string name = def.meta["name"];
        commands[name] = def;
        aliases[name] = name;

        if (def.meta.contains("aliases")) {
            for (const auto& alias : def.meta["aliases"]) {
                aliases[alias] = name;
            }
        }
    }

    inline void registerCommands(const std::vector<CommandDef>& defs) {
        std::unique_lock<std::shared_mutex> lk(lock);
        for (const auto& def : defs) {
            std::string name = def.meta["name"];
            commands[name] = def;
            aliases[name] = name;

            if (def.meta.contains("aliases")) {
                for (const auto& alias : def.meta["aliases"]) {
                    aliases[alias] = name;
                }
            }
        }
    }

inline CommandResult execute(const std::vector<std::string>& args,
                     std::map<std::string, std::string>& state,
                     const std::string& env) const {
    
    if (commands.empty() || aliases.empty()) {
        return {"Commands Registry has no registered commands", {}, {}};
    }

    std::shared_lock<std::shared_mutex> lk(lock);

    if (args.empty()) return {"no command\n", {}, {}};

    std::string cmdName = resolveAlias(args[0]);

    // Handle help command
    if (cmdName == "help" || cmdName == "?") {
        if (args.size() == 1) {
            std::string output = "Available commands:\n";
            for (const auto& [name, def] : commands) {
                output += "  " + name;
                output += "\n";
            }
            return {output, {}, {}};
        } else {
            std::string targetCmd = resolveAlias(args[1]);
            auto it = commands.find(targetCmd);
            if (it != commands.end() && it->second.meta.contains("description")) {
                return {std::string(it->second.meta["description"]) + "\n", {}, {}};
            }
            return {"command not found: " + args[1] + "\n", {}, {}};
        }
    }

    auto cmdIt = commands.find(cmdName);

    if (cmdIt == commands.end()) {
        std::string output = "command not found: " + args[0] + "\nRegistered commands:\n";
        for (const auto& [name, def] : commands) {
            output += "  " + name + "\n";
        }
        return {output, {}, {}};
    }

    const CommandDef& cmd = cmdIt->second;

    if (args.size() > 1 && !cmd.methods.empty()) {
        std::string methodName = resolveMethodAlias(args[1], cmd);
        auto methodIt = cmd.methods.find(methodName);
        
        if (methodIt != cmd.methods.end()) {
            if (!methodIt->second.solver) {
                return {"Method solver is null\n", {}, {}};
            }
            std::vector<std::string> methodArgs(args.begin() + 2, args.end());
            CommandContext ctx{methodArgs, env, state};
            return methodIt->second.solver(ctx);
        }
    }

    if (!cmd.solver) {
        return {"Command solver is null\n", {}, {}};
    }

    CommandContext ctx{std::vector<std::string>(args.begin() + 1, args.end()), env, state};
    return cmd.solver(ctx);
}

};
