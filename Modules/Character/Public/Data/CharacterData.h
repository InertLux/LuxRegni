#pragma once

#include <string>
#include <IDMTemplates.hpp>




//=============================================================================++++=========
//=================++++=====================================================================
struct CharacterData {
    int id = 0;
    std::string path = "";
    double Version = 0.0;

    std::string Name;
    std::string Profile;
    std::string Race;
    std::string Oppinions;
    std::string Faction;
    std::string Friends;
    std::string Flags;
    std::string Tags;

    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Name, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Profile, 4)
    IDM_PROPERTY_ACCESSORS(std::string, Race, 5)
    IDM_PROPERTY_ACCESSORS(std::string, Oppinions, 6)
    IDM_PROPERTY_ACCESSORS(std::string, Faction, 7)
    IDM_PROPERTY_ACCESSORS(std::string, Friends, 8)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 9)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 10)
};

inline constexpr IDMTemplates::ColumnDescriptor CharacterColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version TEXT NOT NULL"},
    {"Name", "Name TEXT"},
    {"Profile", "Profile TEXT"},
    {"Race", "Race TEXT"},
    {"Oppinions", "Oppinions TEXT"},
    {"Faction", "Faction TEXT"},
    {"Friends", "Friends TEXT"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"}
};

inline constexpr IDMTemplates::TableRoute CharacterRoute{
    "/{}/{Character}/{@}/{Character}",
    "RegniRecord",
    "Character",
    false,
    CharacterColumns,
    11
};
inline constexpr IDMTemplates::TableMetadata CharacterMetadata{&CharacterRoute, CharacterColumns, 11};

using CharacterTable = IDMTemplates::DataTypeImpl<
    CharacterData,
    &CharacterMetadata,
    IDMTemplates::Property<int, &CharacterData::id, 0>,
    IDMTemplates::Property<std::string, &CharacterData::path, 1>,
    IDMTemplates::Property<double, &CharacterData::Version, 2>,
    IDMTemplates::Property<std::string, &CharacterData::Name, 3>,
    IDMTemplates::Property<std::string, &CharacterData::Profile, 4>,
    IDMTemplates::Property<std::string, &CharacterData::Race, 5>,
    IDMTemplates::Property<std::string, &CharacterData::Oppinions, 6>,
    IDMTemplates::Property<std::string, &CharacterData::Faction, 7>,
    IDMTemplates::Property<std::string, &CharacterData::Friends, 8>,
    IDMTemplates::Property<std::string, &CharacterData::Flags, 9>,
    IDMTemplates::Property<std::string, &CharacterData::Tags, 10>
>;
//=============================================================================++++=========
//=================++++=====================================================================
struct SocialData {
    int id = -1;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    // Profile Info
    std::string Bio = "";
    std::string Relationship = ""; // Single, Married, Divorced, etc.
    std::string Occupation = "";
    
    // Social Lists
    std::string Friends = "";
    std::string Followers = "";
    std::string Following = "";
    std::string BlockedList = "";
    
    // Reputation & Trust
    float Reputation = 0.0f;
    float ReputationMax = 100.0f;
    float Trust = 0.0f;
    float TrustMax = 100.0f;
    float Loyalty = 0.0f;
    float LoyaltyMax = 100.0f;
    
    // Social Status
    std::string FactionAlignment = "";
    std::string EnemyList = "";
    std::string RivalList = "";
    std::string AlliesList = "";
    
    // Activity
    int FriendsCount = 0;
    int FollowersCount = 0;
    std::string LastSeen = "";
    bool IsOnline = false;

    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)
    IDM_PROPERTY_ACCESSORS(std::string, Bio, 5)
    IDM_PROPERTY_ACCESSORS(std::string, Relationship, 6)
    IDM_PROPERTY_ACCESSORS(std::string, Occupation, 7)
    IDM_PROPERTY_ACCESSORS(std::string, Friends, 8)
    IDM_PROPERTY_ACCESSORS(std::string, Followers, 9)
    IDM_PROPERTY_ACCESSORS(std::string, Following, 10)
    IDM_PROPERTY_ACCESSORS(std::string, BlockedList, 11)
    IDM_PROPERTY_ACCESSORS(float, Reputation, 12)
    IDM_PROPERTY_ACCESSORS(float, ReputationMax, 13)
    IDM_PROPERTY_ACCESSORS(float, Trust, 14)
    IDM_PROPERTY_ACCESSORS(float, TrustMax, 15)
    IDM_PROPERTY_ACCESSORS(float, Loyalty, 16)
    IDM_PROPERTY_ACCESSORS(float, LoyaltyMax, 17)
    IDM_PROPERTY_ACCESSORS(std::string, FactionAlignment, 18)
    IDM_PROPERTY_ACCESSORS(std::string, EnemyList, 19)
    IDM_PROPERTY_ACCESSORS(std::string, RivalList, 20)
    IDM_PROPERTY_ACCESSORS(std::string, AlliesList, 21)
    IDM_PROPERTY_ACCESSORS(int, FriendsCount, 22)
    IDM_PROPERTY_ACCESSORS(int, FollowersCount, 23)
    IDM_PROPERTY_ACCESSORS(std::string, LastSeen, 24)
    IDM_PROPERTY_ACCESSORS(bool, IsOnline, 25)
};

inline constexpr IDMTemplates::ColumnDescriptor SocialColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"},
    {"Bio", "Bio TEXT"},
    {"Relationship", "Relationship TEXT"},
    {"Occupation", "Occupation TEXT"},
    {"Friends", "Friends TEXT"},
    {"Followers", "Followers TEXT"},
    {"Following", "Following TEXT"},
    {"BlockedList", "BlockedList TEXT"},
    {"Reputation", "Reputation REAL"},
    {"ReputationMax", "ReputationMax REAL"},
    {"Trust", "Trust REAL"},
    {"TrustMax", "TrustMax REAL"},
    {"Loyalty", "Loyalty REAL"},
    {"LoyaltyMax", "LoyaltyMax REAL"},
    {"FactionAlignment", "FactionAlignment TEXT"},
    {"EnemyList", "EnemyList TEXT"},
    {"RivalList", "RivalList TEXT"},
    {"AlliesList", "AlliesList TEXT"},
    {"FriendsCount", "FriendsCount INT"},
    {"FollowersCount", "FollowersCount INT"},
    {"LastSeen", "LastSeen TEXT"},
    {"IsOnline", "IsOnline INT"}
};
inline constexpr IDMTemplates::TableRoute SocialRoute{
    "/{}/{Character}/{@}/{Social}",
    "RegniRecord",
    "Character_Social",
    false,
    SocialColumns,
    26
};
inline constexpr IDMTemplates::TableMetadata SocialMetadata{&SocialRoute, SocialColumns, 26};

using SocialTable = IDMTemplates::DataTypeImpl<
    SocialData,
    &SocialMetadata,
    IDMTemplates::Property<int, &SocialData::id, 0>,
    IDMTemplates::Property<std::string, &SocialData::path, 1>,
    IDMTemplates::Property<double, &SocialData::Version, 2>,
    IDMTemplates::Property<std::string, &SocialData::Flags, 3>,
    IDMTemplates::Property<std::string, &SocialData::Tags, 4>,
    IDMTemplates::Property<std::string, &SocialData::Bio, 5>,
    IDMTemplates::Property<std::string, &SocialData::Relationship, 6>,
    IDMTemplates::Property<std::string, &SocialData::Occupation, 7>,
    IDMTemplates::Property<std::string, &SocialData::Friends, 8>,
    IDMTemplates::Property<std::string, &SocialData::Followers, 9>,
    IDMTemplates::Property<std::string, &SocialData::Following, 10>,
    IDMTemplates::Property<std::string, &SocialData::BlockedList, 11>,
    IDMTemplates::Property<float, &SocialData::Reputation, 12>,
    IDMTemplates::Property<float, &SocialData::ReputationMax, 13>,
    IDMTemplates::Property<float, &SocialData::Trust, 14>,
    IDMTemplates::Property<float, &SocialData::TrustMax, 15>,
    IDMTemplates::Property<float, &SocialData::Loyalty, 16>,
    IDMTemplates::Property<float, &SocialData::LoyaltyMax, 17>,
    IDMTemplates::Property<std::string, &SocialData::FactionAlignment, 18>,
    IDMTemplates::Property<std::string, &SocialData::EnemyList, 19>,
    IDMTemplates::Property<std::string, &SocialData::RivalList, 20>,
    IDMTemplates::Property<std::string, &SocialData::AlliesList, 21>,
    IDMTemplates::Property<int, &SocialData::FriendsCount, 22>,
    IDMTemplates::Property<int, &SocialData::FollowersCount, 23>,
    IDMTemplates::Property<std::string, &SocialData::LastSeen, 24>,
    IDMTemplates::Property<bool, &SocialData::IsOnline, 25>
>;
//=============================================================================++++=========
//=================++++=====================================================================
struct HealthData {
    int id = -1;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    float Health = 100;
    float HealthMax = 100;
    float Pain = 0;
    float PainMax = 100;
    float Blood = 100;
    float BloodMax = 100;
    float Stamina = 3;
    float StaminaMax = 100;
    float Adrenaline = 0;
    float AdrenalineMax = 100;
    float Energy = 50;
    float EnergyMax = 100;
    float Hunger = 4;
    float HungerMax = 100;
    float Thirst = 5;
    float ThirstMax = 100;
    float Stress = 6;
    float StressMax = 100;
    float Moral = 7;
    float MoralMax = 100;
    float Immunity = 8;
    float ImmunityMax = 100;
    float Poison = 0;
    float PoisonMax = 100;
    float Toxicity = 0;
    float ToxicityMax = 100;
    float Infestation = 0;
    float InfestationMax = 100;
    
    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)
    IDM_PROPERTY_ACCESSORS(float, Health, 5)
    IDM_PROPERTY_ACCESSORS(float, HealthMax, 6)
    IDM_PROPERTY_ACCESSORS(float, Pain, 7)
    IDM_PROPERTY_ACCESSORS(float, PainMax, 8)
    IDM_PROPERTY_ACCESSORS(float, Blood, 9)
    IDM_PROPERTY_ACCESSORS(float, BloodMax, 10)
    IDM_PROPERTY_ACCESSORS(float, Stamina, 11)
    IDM_PROPERTY_ACCESSORS(float, StaminaMax, 12)
    IDM_PROPERTY_ACCESSORS(float, Adrenaline, 13)
    IDM_PROPERTY_ACCESSORS(float, AdrenalineMax, 14)
    IDM_PROPERTY_ACCESSORS(float, Energy, 15)
    IDM_PROPERTY_ACCESSORS(float, EnergyMax, 16)
    IDM_PROPERTY_ACCESSORS(float, Hunger, 17)
    IDM_PROPERTY_ACCESSORS(float, HungerMax, 18)
    IDM_PROPERTY_ACCESSORS(float, Thirst, 19)
    IDM_PROPERTY_ACCESSORS(float, ThirstMax, 20)
    IDM_PROPERTY_ACCESSORS(float, Stress, 21)
    IDM_PROPERTY_ACCESSORS(float, StressMax, 22)
    IDM_PROPERTY_ACCESSORS(float, Moral, 23)
    IDM_PROPERTY_ACCESSORS(float, MoralMax, 24)
    IDM_PROPERTY_ACCESSORS(float, Immunity, 25)
    IDM_PROPERTY_ACCESSORS(float, ImmunityMax, 26)
    IDM_PROPERTY_ACCESSORS(float, Poison, 27)
    IDM_PROPERTY_ACCESSORS(float, PoisonMax, 28)
    IDM_PROPERTY_ACCESSORS(float, Toxicity, 29)
    IDM_PROPERTY_ACCESSORS(float, ToxicityMax, 30)
    IDM_PROPERTY_ACCESSORS(float, Infestation, 31)
    IDM_PROPERTY_ACCESSORS(float, InfestationMax, 32)
};

inline constexpr IDMTemplates::ColumnDescriptor HealthColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"},
    {"Health", "Health REAL"},
    {"HealthMax", "HealthMax REAL"},
    {"Pain", "Pain REAL"},
    {"PainMax", "PainMax REAL"},
    {"Blood", "Blood REAL"},
    {"BloodMax", "BloodMax REAL"},
    {"Stamina", "Stamina REAL"},
    {"StaminaMax", "StaminaMax REAL"},
    {"Adrenaline", "Adrenaline REAL"},
    {"AdrenalineMax", "AdrenalineMax REAL"},
    {"Energy", "Energy REAL"},
    {"EnergyMax", "EnergyMax REAL"},
    {"Hunger", "Hunger REAL"},
    {"HungerMax", "HungerMax REAL"},
    {"Thirst", "Thirst REAL"},
    {"ThirstMax", "ThirstMax REAL"},
    {"Stress", "Stress REAL"},
    {"StressMax", "StressMax REAL"},
    {"Moral", "Moral REAL"},
    {"MoralMax", "MoralMax REAL"},
    {"Immunity", "Immunity REAL"},
    {"ImmunityMax", "ImmunityMax REAL"},
    {"Poison", "Poison REAL"},
    {"PoisonMax", "PoisonMax REAL"},
    {"Toxicity", "Toxicity REAL"},
    {"ToxicityMax", "ToxicityMax REAL"},
    {"Infestation", "Infestation REAL"},
    {"InfestationMax", "InfestationMax REAL"}
};

inline constexpr IDMTemplates::TableRoute HealthRoute{
    "/{}/{Character}/{@}/{Health}",
    "RegniRecord",
    "Character_Health",
    false,
    HealthColumns,
    33
};

inline constexpr IDMTemplates::TableMetadata HealthMetadata{&HealthRoute, HealthColumns, 33};

using HealthTable = IDMTemplates::DataTypeImpl<
    HealthData,
    &HealthMetadata,
    IDMTemplates::Property<int, &HealthData::id, 0>,
    IDMTemplates::Property<std::string, &HealthData::path, 1>,
    IDMTemplates::Property<double, &HealthData::Version, 2>,
    IDMTemplates::Property<std::string, &HealthData::Flags, 3>,
    IDMTemplates::Property<std::string, &HealthData::Tags, 4>,
    IDMTemplates::Property<float, &HealthData::Health, 5>,
    IDMTemplates::Property<float, &HealthData::HealthMax, 6>,
    IDMTemplates::Property<float, &HealthData::Pain, 7>,
    IDMTemplates::Property<float, &HealthData::PainMax, 8>,
    IDMTemplates::Property<float, &HealthData::Blood, 9>,
    IDMTemplates::Property<float, &HealthData::BloodMax, 10>,
    IDMTemplates::Property<float, &HealthData::Stamina, 11>,
    IDMTemplates::Property<float, &HealthData::StaminaMax, 12>,
    IDMTemplates::Property<float, &HealthData::Adrenaline, 13>,
    IDMTemplates::Property<float, &HealthData::AdrenalineMax, 14>,
    IDMTemplates::Property<float, &HealthData::Energy, 15>,
    IDMTemplates::Property<float, &HealthData::EnergyMax, 16>,
    IDMTemplates::Property<float, &HealthData::Hunger, 17>,
    IDMTemplates::Property<float, &HealthData::HungerMax, 18>,
    IDMTemplates::Property<float, &HealthData::Thirst, 19>,
    IDMTemplates::Property<float, &HealthData::ThirstMax, 20>,
    IDMTemplates::Property<float, &HealthData::Stress, 21>,
    IDMTemplates::Property<float, &HealthData::StressMax, 22>,
    IDMTemplates::Property<float, &HealthData::Moral, 23>,
    IDMTemplates::Property<float, &HealthData::MoralMax, 24>,
    IDMTemplates::Property<float, &HealthData::Immunity, 25>,
    IDMTemplates::Property<float, &HealthData::ImmunityMax, 26>,
    IDMTemplates::Property<float, &HealthData::Poison, 27>,
    IDMTemplates::Property<float, &HealthData::PoisonMax, 28>,
    IDMTemplates::Property<float, &HealthData::Toxicity, 29>,
    IDMTemplates::Property<float, &HealthData::ToxicityMax, 30>,
    IDMTemplates::Property<float, &HealthData::Infestation, 31>,
    IDMTemplates::Property<float, &HealthData::InfestationMax, 32>
>;

//=============================================================================++++=========
//=================++++=====================================================================

struct SkillsData{

    int id = -1;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    int Experience = 1;
    int Level = 1;
    int Intellegence = 1;
    int Intuition = 1;
    int Wisdom = 1;
    int Scholastic = 1;
    int Strength = 1;
    int Dexterity = 1;
    int Will = 1;
    int Fervor = 1;
    int Reception = 1;
    int Conception = 1;
    int Knowing = 1;
    int Envision = 1;
    int Silence = 1;
    int Heart = 1;
    int Guile = 1;
    int Saint = 1;

    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)

    IDM_PROPERTY_ACCESSORS(int, Experience, 3)
    IDM_PROPERTY_ACCESSORS(int, Level, 4)
    IDM_PROPERTY_ACCESSORS(int, Intellegence, 5)
    IDM_PROPERTY_ACCESSORS(int, Intuition, 6)
    IDM_PROPERTY_ACCESSORS(int, Wisdom, 7)
    IDM_PROPERTY_ACCESSORS(int, Scholastic, 8)
    IDM_PROPERTY_ACCESSORS(int, Strength, 9)
    IDM_PROPERTY_ACCESSORS(int, Dexterity, 10)
    IDM_PROPERTY_ACCESSORS(int, Will, 11)
    IDM_PROPERTY_ACCESSORS(int, Fervor, 12)
    IDM_PROPERTY_ACCESSORS(int, Reception, 13)
    IDM_PROPERTY_ACCESSORS(int, Conception, 14)
    IDM_PROPERTY_ACCESSORS(int, Knowing, 15)
    IDM_PROPERTY_ACCESSORS(int, Envision, 16)
    IDM_PROPERTY_ACCESSORS(int, Silence, 17)
    IDM_PROPERTY_ACCESSORS(int, Heart, 18)
    IDM_PROPERTY_ACCESSORS(int, Guile, 19)
    IDM_PROPERTY_ACCESSORS(int, Saint, 20)
};
// Character (root)
inline constexpr IDMTemplates::ColumnDescriptor SkillsColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Name TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},

    {"Experience", "Experience TEXT"},
    {"Level", "Level TEXT"},
    {"Intellegence", "Intellegence TEXT"},
    {"Intuition", "Intuition TEXT"},
    {"Wisdom", "Wisdom TEXT"},
    {"Scholastic", "Scholastic TEXT"},
    {"Strength", "Strength TEXT"},
    {"Dexterity", "Dexterity TEXT"},
    {"Will", "Will TEXT"},
    {"Fervor", "Fervor TEXT"},
    {"Reception", "Reception TEXT"},
    {"Conception", "Conception TEXT"},
    {"Knowing", "Knowing TEXT"},
    {"Envision", "Envision TEXT"},
    {"Silence", "Silence TEXT"},
    {"Heart", "Heart TEXT"},
    {"Guile", "Guile TEXT"},
    {"Saint", "Saint TEXT"}
};
inline constexpr IDMTemplates::TableRoute SkillsRoute{
    "/{}/{Character}/{@}/{Skills}",
    "RegniRecord",
    "Character_Skills",
    false,
    SkillsColumns,
    21
};
inline constexpr IDMTemplates::TableMetadata SkillsMetadata{&SkillsRoute, SkillsColumns, 21};

using SkillsTable = IDMTemplates::DataTypeImpl<
    SkillsData,
    &SkillsMetadata,
    IDMTemplates::Property<int, &SkillsData::id, 0>,
    IDMTemplates::Property<std::string, &SkillsData::path, 1>,
    IDMTemplates::Property<double, &SkillsData::Version, 2>,
    
    IDMTemplates::Property<int, &SkillsData::Experience, 3>,
    IDMTemplates::Property<int, &SkillsData::Level, 4>,
    IDMTemplates::Property<int, &SkillsData::Intellegence, 5>,
    IDMTemplates::Property<int, &SkillsData::Intuition, 6>,
    IDMTemplates::Property<int, &SkillsData::Wisdom, 7>,
    IDMTemplates::Property<int, &SkillsData::Scholastic, 8>,
    IDMTemplates::Property<int, &SkillsData::Strength, 9>,
    IDMTemplates::Property<int, &SkillsData::Dexterity, 10>,
    IDMTemplates::Property<int, &SkillsData::Will, 11>,
    IDMTemplates::Property<int, &SkillsData::Fervor, 12>,
    IDMTemplates::Property<int, &SkillsData::Reception, 13>,
    IDMTemplates::Property<int, &SkillsData::Conception, 14>,
    IDMTemplates::Property<int, &SkillsData::Knowing, 15>,
    IDMTemplates::Property<int, &SkillsData::Envision, 16>,
    IDMTemplates::Property<int, &SkillsData::Silence, 17>,
    IDMTemplates::Property<int, &SkillsData::Heart, 18>,
    IDMTemplates::Property<int, &SkillsData::Guile, 19>,
    IDMTemplates::Property<int, &SkillsData::Saint, 20>
>;
//=============================================================================++++=========
//=================++++=====================================================================





// Inventory data
struct InventoryData {
    int id = -1;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    std::string Inventory = "";

    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)
    IDM_PROPERTY_ACCESSORS(std::string, Inventory, 5)
};

inline constexpr IDMTemplates::ColumnDescriptor InventoryColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"},
    {"Inventory", "Inventory TEXT"}
};

inline constexpr IDMTemplates::TableRoute InventoryRoute{
    "/{}/{Character}/{@}/{Inventory}",
    "RegniRecord",
    "Character_Inventory",
    false,
    InventoryColumns,
    6
};

inline constexpr IDMTemplates::TableMetadata InventoryMetadata{&InventoryRoute, InventoryColumns, 6};

using InventoryTable = IDMTemplates::DataTypeImpl<
    InventoryData,
    &InventoryMetadata,
    IDMTemplates::Property<int, &InventoryData::id, 0>,
    IDMTemplates::Property<std::string, &InventoryData::path, 1>,
    IDMTemplates::Property<double, &InventoryData::Version, 2>,
    IDMTemplates::Property<std::string, &InventoryData::Flags, 3>,
    IDMTemplates::Property<std::string, &InventoryData::Tags, 4>,
    IDMTemplates::Property<std::string, &InventoryData::Inventory, 5>
>;

//=============================================================================++++=========
//=================++++=====================================================================

// Backpack data
struct BackpackData {
    int id = -1;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    std::string Inventory = "";

    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)
    IDM_PROPERTY_ACCESSORS(std::string, Inventory, 5)
};

inline constexpr IDMTemplates::ColumnDescriptor BackpackColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"},
    {"Inventory", "Inventory TEXT"}
};
inline constexpr IDMTemplates::TableRoute BackpackRoute{
    "/{}/{Character}/{@}/{Backpack}",
    "RegniRecord",
    "Character_Backpack",
    false,
    BackpackColumns,
    6
};
inline constexpr IDMTemplates::TableMetadata BackpackMetadata{&BackpackRoute, BackpackColumns, 6};

using BackpackTable = IDMTemplates::DataTypeImpl<
    BackpackData,
    &BackpackMetadata,
    IDMTemplates::Property<int, &BackpackData::id, 0>,
    IDMTemplates::Property<std::string, &BackpackData::path, 1>,
    IDMTemplates::Property<double, &BackpackData::Version, 2>,
    IDMTemplates::Property<std::string, &BackpackData::Flags, 3>,
    IDMTemplates::Property<std::string, &BackpackData::Tags, 4>,
    IDMTemplates::Property<std::string, &BackpackData::Inventory, 5>
>;

//=============================================================================++++=========
//=================++++=====================================================================

// Equipment data
struct EquipmentData {
    int id = -1;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    std::string Inventory = "";

    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)
    IDM_PROPERTY_ACCESSORS(std::string, Inventory, 5)
};

inline constexpr IDMTemplates::ColumnDescriptor EquipmentColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"},
    {"Inventory", "Inventory TEXT"}
};

inline constexpr IDMTemplates::TableRoute EquipmentRoute{
    "/{}/{Character}/{@}/{Equipment}",
    "RegniRecord",
    "Character_Equipment",
    false,
    EquipmentColumns,
    6
};
inline constexpr IDMTemplates::TableMetadata EquipmentMetadata{&CharacterRoute, EquipmentColumns, 6};

using EquipmentTable = IDMTemplates::DataTypeImpl<
    EquipmentData,
    &EquipmentMetadata,
    IDMTemplates::Property<int, &EquipmentData::id, 0>,
    IDMTemplates::Property<std::string, &EquipmentData::path, 1>,
    IDMTemplates::Property<double, &EquipmentData::Version, 2>,
    IDMTemplates::Property<std::string, &EquipmentData::Flags, 3>,
    IDMTemplates::Property<std::string, &EquipmentData::Tags, 4>,
    IDMTemplates::Property<std::string, &EquipmentData::Inventory, 5>
>;

//=============================================================================++++=========
//=================++++=====================================================================


