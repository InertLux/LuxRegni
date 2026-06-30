
#pragma once

#include <string>
#include <IDMTemplates.hpp>










struct WeaponData {
    int id = 0;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    float Damage = 0.0f;
    int AttackSpeed = 0;
    std::string DamageType;
    float Durability = 100.0f;
    float MaxDurability = 100.0f;

    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)
    IDM_PROPERTY_ACCESSORS(float, Damage, 5)
    IDM_PROPERTY_ACCESSORS(int, AttackSpeed, 6)
    IDM_PROPERTY_ACCESSORS(std::string, DamageType, 7)
    IDM_PROPERTY_ACCESSORS(float, Durability, 8)
    IDM_PROPERTY_ACCESSORS(float, MaxDurability, 9)
};



inline constexpr IDMTemplates::ColumnDescriptor WeaponColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"},
    {"Damage", "Damage FLOAT"},
    {"AttackSpeed", "AttackSpeed INT"},
    {"DamageType", "DamageType TEXT"},
    {"Durability", "Durability FLOAT"},
    {"MaxDurability", "MaxDurability FLOAT"}
};
inline constexpr IDMTemplates::TableRoute WeaponRoute{
    "/{}/{Item}/{@}/{Weapon}",
    "RegniRecord",
    "Item_Weapon",
    false,
    WeaponColumns,
    10
};
inline constexpr IDMTemplates::TableMetadata WeaponMetadata{&WeaponRoute, WeaponColumns, 10};

using WeaponTable = IDMTemplates::DataTypeImpl<
    WeaponData,
    &WeaponMetadata,
    IDMTemplates::Property<int, &WeaponData::id, 0>,
    IDMTemplates::Property<std::string, &WeaponData::path, 1>,
    IDMTemplates::Property<double, &WeaponData::Version, 2>,
    IDMTemplates::Property<std::string, &WeaponData::Flags, 3>,
    IDMTemplates::Property<std::string, &WeaponData::Tags, 4>,
    IDMTemplates::Property<float, &WeaponData::Damage, 5>,
    IDMTemplates::Property<int, &WeaponData::AttackSpeed, 6>,
    IDMTemplates::Property<std::string, &WeaponData::DamageType, 7>,
    IDMTemplates::Property<float, &WeaponData::Durability, 8>,
    IDMTemplates::Property<float, &WeaponData::MaxDurability, 9>
>;

class WeaponShard : public IDMTemplates::Shard<WeaponData, WeaponTable> {
public:
        WeaponShard(std::shared_ptr<DatabaseRouterImpl> router, const std::string& path)
        : IDMTemplates::Shard<WeaponData, WeaponTable>(router, path) {}
};

