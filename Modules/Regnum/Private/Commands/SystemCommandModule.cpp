#include "SystemCommandModule.h"
#include "Regnum.h"

CommandResult SystemCommandModule::Execute_Init(const CommandContext& ctx)
{
    std::string output = "Init Regnum \n";
    return {output, {}, {}};
};
CommandResult SystemCommandModule::Execute_Shutdown(const CommandContext& ctx){
    std::string output = "Shutdown Regnum \n";
    return {output, {}, {}};
}


CommandResult SystemCommandModule::Execute_ListProjects(const CommandContext& ctx){
    std::string output = "List Regnum \n";
    return {output, {}, {}};
}


CommandResult SystemCommandModule::Execute_CreateProject(const CommandContext& ctx){
    std::string output = "Create Regnum \n";
    return {output, {}, {}};
}
CommandResult SystemCommandModule::Execute_DeleteProject(const CommandContext& ctx){
    std::string output = "Delete Regnum \n";
    return {output, {}, {}};
}


CommandResult SystemCommandModule::Execute_OpenProject(const CommandContext& ctx){
    std::string output = "Open Regnum \n";
    return {output, {}, {}};
}
CommandResult SystemCommandModule::Execute_CloseProject(const CommandContext& ctx){
    std::string output = "Close Regnum \n";
    return {output, {}, {}};
}
CommandResult SystemCommandModule::Execute_NewShard(const CommandContext& ctx){
    std::string output = "Shard Regnum \n";
    return {output, {}, {}};
}
CommandResult SystemCommandModule::Execute_NewBase(const CommandContext& ctx){
    std::string output = "new-base Regnum \n";
    return {output, {}, {}};
}
