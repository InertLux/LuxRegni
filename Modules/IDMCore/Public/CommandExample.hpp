// Modules/IDMCore/CommandExample.hpp

#pragma once
#include "CommandRegistry.h"
#include "CommandClasses.h"
#include <memory>
#include <string>




class SampleCommandModule : public CommandModule {
public:
    SampleCommandModule() = default;
    
    inline std::vector<CommandDef> getCommands() override {
        return {
            CommandDef{
                json::parse(R"({
                    "name": "print",
                    "aliases": ["pr"],
                    "category": "Utility",
                    "description": "Print to log"
                })"),
                [](const CommandContext& ctx) -> CommandResult {
                  if (ctx.args.empty()) return {"", {}, {}};

                  std::string output;
                  for (size_t i = 0; i < ctx.args.size(); ++i) {
                    output += ctx.args[i];
                    if (i < ctx.args.size() - 1) output += " ";
                  }
                  output += "\n";
                     
                  return {output, {}, {}};
                },
                {}
            }
        };
    }
};