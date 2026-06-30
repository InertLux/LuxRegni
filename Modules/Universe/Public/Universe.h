#pragma once

#include <string>
#include <memory>

#include <IDMTemplates.hpp>
#include "Data/UniverseData.h"



//=============================================================================++++=========
// UNIVERSE OBJECT (Simulation + IO)
//=============================================================================++++=========
class Universe : public IDMTemplates::RootObject<
    UniverseData,
    UniverseTable
> {
public:
    Universe(std::shared_ptr<DatabaseRouterImpl> router, const std::string& objectPath)
    : RootObject(router, objectPath) {}
};

using Universe_Inst = IDMObject_Inst<Universe>;


