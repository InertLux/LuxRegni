#include "CharacterCommandModule.h"
#include "Regnum.h"



CommandResult CharacterCommandModule::Execute_List(const CommandContext& ctx){
    auto Reg = Regnum::Get();

    std::string output = "Close Regnum \n";
    return {output, {}, {}};
}
CommandResult CharacterCommandModule::Execute_Edit(const CommandContext& ctx){
    auto Reg = Regnum::Get();

    std::string output = "Shard Regnum \n";
    return {output, {}, {}};
}
CommandResult CharacterCommandModule::Execute_Delete(const CommandContext& ctx){
    auto Reg = Regnum::Get();
    
    std::string output = "new-base Regnum \n";
    return {output, {}, {}};
}