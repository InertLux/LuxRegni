#pragma once

#include <string>
#include <IDMTemplates.hpp>
#include "Data/ItemData.h"
#include "Data/Crevi.h"
#include "Data/Equipment.h"
#include "Data/Weapons.h"
#include "Data/Consumeables.h"
#include "Data/Tools.h"
#include "Data/Artifacts.h"






class Item : public IDMTemplates::RootObject<
    ItemData,
    ItemTable,
    FoodShard,
    IngredientShard,
    SalveShard,
    GrenadeShard,
    TurretShard,
    AutomatonShard,
    ConveyorShard,
    WeaponShard,
    ArmorShard
> {
public:
    Item(std::shared_ptr<DatabaseRouterImpl> router, const std::string& objectPath)
    : RootObject(router, objectPath) {}
            
    // Declare routing rules for this RootObject and its collections
    // Needs to be called by game instace once. after initializing Router
    static void RegisterGameObject(DatabaseRouterImpl* router) {
        //router->RegisterRoute("/{}/{Character}/{@}/{Social}", "RegniRecord", "Social");
        
        //router->RegisterRoute("/Item/Item/.*");
        //router->RegisterRoute("/Item/Food/.*");
        //router->RegisterRoute("/Item/Ingredient/.*");
        //router->RegisterRoute("/Item/Salve/.*");
        //router->RegisterRoute("/Item/Grenade/.*");
        //router->RegisterRoute("/Item/Turret/.*");
        //router->RegisterRoute("/Item/Automaton/.*");
        //router->RegisterRoute("/Item/Conveyor/.*");
        //router->RegisterRoute("/Item/Weapon/.*");
        //router->RegisterRoute("/Item/Armor/.*");
    }
};

using Item_Inst = IDMObject_Inst<Item>;


