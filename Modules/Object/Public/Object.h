#pragma once
#include <sqlite3.h>
#include <memory>
#include <unordered_map>
#include <string>

// Include all object headers
#include "Data/Chest.h"
#include "Data/Resource.h"
#include "Data/Tree.h"
#include "Data/ObjectData.h"


class GameObject : public IDMTemplates::RootObject<
    GameObjectData,
    GameObjectTable,
    ChestShard,
    ResourceShard,
    TreeShard
>  {
    public:
        GameObject(std::shared_ptr<DatabaseRouterImpl> router, const std::string& objectPath)
        : RootObject(router, objectPath) {}

public:
    GameObject() = default;
};

using GameObject_Inst = IDMObject_Inst<GameObject>;