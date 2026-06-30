
#pragma once
#include <string>
#include <IDMTemplates.hpp>
#include "Data/RegionData.h"



//=============================================================================++++=========
// REGION OBJECT (Simulation + IO)
//=============================================================================++++=========



class Region : public IDMTemplates::RootObject<
    RegionData,
    RegionTable
> {
public:
    Region(std::shared_ptr<DatabaseRouterImpl> router, const std::string& objectPath)
    : RootObject(router, objectPath) {}
            
    // Declare routing rules for this RootObject and its collections
    // Needs to be called by game instace once. after initializing Router
    static void RegisterGameObject(std::shared_ptr<DatabaseRouterImpl> router) {
                //router->RegisterRoute("/{}/{Character}/{@}/{Social}", "RegniRecord", "Social");
        
    }
};

using Region_Inst = IDMObject_Inst<Region>;