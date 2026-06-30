#pragma once

#include <string>
#include <IDMTemplates.hpp>
#include "Data/WorldData.h"





//=============================================================================++++=========
// WORLD OBJECT (Simulation + IO)
//=============================================================================++++=========

class World : public IDMTemplates::RootObject<
    WorldData,
    WorldTable
> {
public:
    World(std::shared_ptr<DatabaseRouterImpl> router, const std::string& objectPath)
    : RootObject(router, objectPath) {}
};


using World_Inst = IDMObject_Inst<World>;