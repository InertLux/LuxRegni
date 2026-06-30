#pragma once

#include <string>
#include <IDMTemplates.hpp>




struct ArmorData {
    int id = 0;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    int Slot = 0;
    float ArmorRating = 0.0f;
    float MagicResistance = 0.0f;
    std::string Effect;
    float Durability = 100.0f;
    float MaxDurability = 100.0f;

    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)
    IDM_PROPERTY_ACCESSORS(int, Slot, 5)
    IDM_PROPERTY_ACCESSORS(float, ArmorRating, 6)
    IDM_PROPERTY_ACCESSORS(float, MagicResistance, 7)
    IDM_PROPERTY_ACCESSORS(std::string, Effect, 8)
    IDM_PROPERTY_ACCESSORS(float, Durability, 9)
    IDM_PROPERTY_ACCESSORS(float, MaxDurability, 10)
};
inline constexpr IDMTemplates::ColumnDescriptor ArmorColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"},
    {"Slot", "Slot INT"},
    {"ArmorRating", "ArmorRating FLOAT"},
    {"MagicResistance", "MagicResistance FLOAT"},
    {"Effect", "Effect TEXT"},
    {"Durability", "Durability FLOAT"},
    {"MaxDurability", "MaxDurability FLOAT"}
};

inline constexpr IDMTemplates::TableRoute ArmorRoute{
    "/{}/{Item}/{@}/{Armor}",
    "RegniRecord",
    "Item_Armor",
    false,
    ArmorColumns,
    11
};
inline constexpr IDMTemplates::TableMetadata ArmorMetadata{&ArmorRoute, ArmorColumns, 11};

using ArmorTable = IDMTemplates::DataTypeImpl<
    ArmorData,
    &ArmorMetadata,
    IDMTemplates::Property<int, &ArmorData::id, 0>,
    IDMTemplates::Property<std::string, &ArmorData::path, 1>,
    IDMTemplates::Property<double, &ArmorData::Version, 2>,
    IDMTemplates::Property<std::string, &ArmorData::Flags, 3>,
    IDMTemplates::Property<std::string, &ArmorData::Tags, 4>,
    IDMTemplates::Property<int, &ArmorData::Slot, 5>,
    IDMTemplates::Property<float, &ArmorData::ArmorRating, 6>,
    IDMTemplates::Property<float, &ArmorData::MagicResistance, 7>,
    IDMTemplates::Property<std::string, &ArmorData::Effect, 8>,
    IDMTemplates::Property<float, &ArmorData::Durability, 9>,
    IDMTemplates::Property<float, &ArmorData::MaxDurability, 10>
>;

class ArmorShard : public IDMTemplates::Shard<ArmorData, ArmorTable> {
public:
        ArmorShard(std::shared_ptr<DatabaseRouterImpl> router, const std::string& path)
        : IDMTemplates::Shard<ArmorData, ArmorTable>(router, path) {}
};

