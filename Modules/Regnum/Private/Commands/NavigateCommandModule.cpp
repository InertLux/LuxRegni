#include "Commands.h"
#include "Regnum.h"



CommandResult NavigateCommandModule::Execute_Navigate(const CommandContext& ctx) {

    static const std::map<std::string, CommandBundle::CommandDomain> domains{
        {".", CommandBundle::CommandDomain::CR_Global},
        {"global", CommandBundle::CommandDomain::CR_Global},
        {"home", CommandBundle::CommandDomain::CR_Global},
        {"regni", CommandBundle::CommandDomain::CR_System},
        {"system", CommandBundle::CommandDomain::CR_System},
        {"sys", CommandBundle::CommandDomain::CR_Global},
        {"universe", CommandBundle::CommandDomain::CR_Universe},
        {"u", CommandBundle::CommandDomain::CR_Universe},
        {"world", CommandBundle::CommandDomain::CR_World},
        {"w", CommandBundle::CommandDomain::CR_World},
        {"region", CommandBundle::CommandDomain::CR_Region},
        {"r", CommandBundle::CommandDomain::CR_Region},
        {"place", CommandBundle::CommandDomain::CR_Place},
        {"p", CommandBundle::CommandDomain::CR_Place},
        {"character", CommandBundle::CommandDomain::CR_Character},
        {"c", CommandBundle::CommandDomain::CR_Character},
        {"object", CommandBundle::CommandDomain::CR_Object},
        {"o", CommandBundle::CommandDomain::CR_Object},
        {"item", CommandBundle::CommandDomain::CR_Item},
        {"i", CommandBundle::CommandDomain::CR_Item}
    };
        static std::string g = "\n\033[1;37m Reg-app    \033[0m . global home       \n"; 
        static std::string s = "\033[1;37m[Reg-sys]   \033[0m regni system sys     \n";
        static std::string u = "\033[1;36m[Universe]  \033[0m universe u          \n";
        static std::string w = "\033[1;32m[World]     \033[0m world w              \n";
        static std::string r = "\033[1;33m[Region]    \033[0m region r             \n";
        static std::string p = "\033[1;35m[Place]     \033[0m place p              \n";
        static std::string c = "\033[1;31m[Character] \033[0m character char c    \n";
        static std::string o = "\033[0;37m[Object]    \033[0m object obj o        \n";
        static std::string i = "\033[1;34m[Item]      \033[0m item itm i           \n\n";

        static std::string list = g+s+u+w+r+p+c+o+i; 
    if (ctx.args.empty()){return {list,{},{}};}
    if(ctx.args[0] == "list"){return {list,{},{}};}


    auto it = domains.find(ctx.args[0]);
    if (it == domains.end()) return {"Error: unknown domain\n", {}, {}};
    
    Regnum::Get()->cm_domain = it->second;
    return {"Navigated to " + ctx.args[0] + "\n", {}, {}};
}