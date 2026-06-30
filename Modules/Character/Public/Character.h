#pragma once

#include <string>
#include <IDMTemplates.hpp>
#include "Data/CharacterData.h"

/*
CharacterData
    Name
    Profile
    Race
    Oppinions
    Faction
    Friends
HealthData

SkillsData
BackpackData
EquipmentData
InventoryData
LootDropData
*/









class SocialShard : public IDMTemplates::Shard<SocialData, SocialTable> {
public:
        SocialShard(std::shared_ptr<DatabaseRouterImpl> router, const std::string& path)
        : IDMTemplates::Shard<SocialData, SocialTable>(router, path) {}
};

class HealthShard : public IDMTemplates::Shard<HealthData, HealthTable> {
public:
        HealthShard(std::shared_ptr<DatabaseRouterImpl> router, const std::string& path)
        : IDMTemplates::Shard<HealthData, HealthTable>(router, path) {}
};

class SkillsShard : public IDMTemplates::Shard<SkillsData, SkillsTable> {
public:
        SkillsShard(std::shared_ptr<DatabaseRouterImpl> router, const std::string& path)
        : IDMTemplates::Shard<SkillsData, SkillsTable>(router, path) {}
};

class InventoryShard : public IDMTemplates::Shard<InventoryData, InventoryTable> {
public:
        InventoryShard(std::shared_ptr<DatabaseRouterImpl> router, const std::string& path)
        : IDMTemplates::Shard<InventoryData, InventoryTable>(router, path) {}
};

class BackpackShard : public IDMTemplates::Shard<BackpackData, BackpackTable> {
public:
        BackpackShard(std::shared_ptr<DatabaseRouterImpl> router, const std::string& path)
        : IDMTemplates::Shard<BackpackData, BackpackTable>(router, path) {}
};

class EquipmentShard : public IDMTemplates::Shard<EquipmentData, EquipmentTable> {
public:
        EquipmentShard(std::shared_ptr<DatabaseRouterImpl> router, const std::string& path)
        : IDMTemplates::Shard<EquipmentData, EquipmentTable>(router, path) {}
};




// ============================================================================
// Character Object (Simulation + IO)
// ============================================================================

class Character : public IDMTemplates::RootObject<
    CharacterData,
    CharacterTable,
    SocialShard,
    HealthShard,
    SkillsShard,
    InventoryShard,
    BackpackShard,
    EquipmentShard
    
>  {
    

public:
    Character(std::shared_ptr<DatabaseRouterImpl> router, const std::string& objectPath)
        : RootObject(router, objectPath) 
        {
            GetCharacterData().path = objectPath;
            GetCharacterData().Version = 0;

        }

    CharacterData& GetCharacterData(){return m_data;}
    



    // Accessors
//    int32_t GetId() const { return id; }
//    std::string GetName() const { return name; }
//    std::string GetClass() const { return characterClass; }
//    int32_t GetHealth() const { return health; }
//    int32_t GetLevel() const { return level; }
//    int32_t GetExperience() const { return experience; }

    // Mutators
//    void SetName(const std::string& newName) { name = newName; }
//    void SetClass(const std::string& newClass) { characterClass = newClass; }
//    void SetHealth(int32_t hp) { health = hp; }
//    void SetLevel(int32_t lvl) { level = lvl; }
//    void SetExperience(int32_t xp) { experience = xp; }

    // IO Operations
    // bool Load(const std::string& path); 
    // bool Save(const std::string& path);

    // Simulation
//    void TakeDamage(int32_t amount);
//    void GainExperience(int32_t amount);
};
using Character_Inst = IDMObject_Inst<Character>;

