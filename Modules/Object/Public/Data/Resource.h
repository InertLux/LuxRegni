#pragma once

#include <string>
#include <IDMTemplates.hpp>

struct ResourceData {
    int id = 0;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    std::string Name;
    std::string Description;
    std::string RegionPath;
    std::string ResourceType;
    float LocationX = 0.0f;
    float LocationY = 0.0f;
    float LocationZ = 0.0f;
    int Quantity = 0;
    float Rarity = 0.0f;
    bool IsRenewable = false;
    float RespawnRate = 0.0f;
    std::string Quality;
    std::string Metadata;
    
    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)
    IDM_PROPERTY_ACCESSORS(std::string, Name, 5)
    IDM_PROPERTY_ACCESSORS(std::string, Description, 6)
    IDM_PROPERTY_ACCESSORS(std::string, RegionPath, 7)
    IDM_PROPERTY_ACCESSORS(std::string, ResourceType, 8)
    IDM_PROPERTY_ACCESSORS(float, LocationX, 9)
    IDM_PROPERTY_ACCESSORS(float, LocationY, 10)
    IDM_PROPERTY_ACCESSORS(float, LocationZ, 11)
    IDM_PROPERTY_ACCESSORS(int, Quantity, 12)
    IDM_PROPERTY_ACCESSORS(float, Rarity, 13)
    IDM_PROPERTY_ACCESSORS(bool, IsRenewable, 14)
    IDM_PROPERTY_ACCESSORS(float, RespawnRate, 15)
    IDM_PROPERTY_ACCESSORS(std::string, Quality, 16)
    IDM_PROPERTY_ACCESSORS(std::string, Metadata, 17)
};

inline constexpr IDMTemplates::ColumnDescriptor ResourceColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"},
    {"Name", "Name TEXT"},
    {"Description", "Description TEXT"},
    {"RegionPath", "RegionPath TEXT"},
    {"ResourceType", "ResourceType TEXT"},
    {"LocationX", "LocationX REAL"},
    {"LocationY", "LocationY REAL"},
    {"LocationZ", "LocationZ REAL"},
    {"Quantity", "Quantity INT"},
    {"Rarity", "Rarity REAL"},
    {"IsRenewable", "IsRenewable INT"},
    {"RespawnRate", "RespawnRate REAL"},
    {"Quality", "Quality TEXT"},
    {"Metadata", "Metadata TEXT"}
};

inline constexpr IDMTemplates::TableRoute ResourceRoute{
    "/{}/{Object}/{@}/{Resource}",
    "RegniRecord",
    "Object_Resource",
    false,
    ResourceColumns,
    18
};

inline constexpr IDMTemplates::TableMetadata ResourceMetadata{&ResourceRoute, ResourceColumns, 18};

using ResourceTable = IDMTemplates::DataTypeImpl<
    ResourceData,
    &ResourceMetadata,
    IDMTemplates::Property<int, &ResourceData::id, 0>,
    IDMTemplates::Property<std::string, &ResourceData::path, 1>,
    IDMTemplates::Property<double, &ResourceData::Version, 2>,
    IDMTemplates::Property<std::string, &ResourceData::Flags, 3>,
    IDMTemplates::Property<std::string, &ResourceData::Tags, 4>,
    IDMTemplates::Property<std::string, &ResourceData::Name, 5>,
    IDMTemplates::Property<std::string, &ResourceData::Description, 6>,
    IDMTemplates::Property<std::string, &ResourceData::RegionPath, 7>,
    IDMTemplates::Property<std::string, &ResourceData::ResourceType, 8>,
    IDMTemplates::Property<float, &ResourceData::LocationX, 9>,
    IDMTemplates::Property<float, &ResourceData::LocationY, 10>,
    IDMTemplates::Property<float, &ResourceData::LocationZ, 11>,
    IDMTemplates::Property<int, &ResourceData::Quantity, 12>,
    IDMTemplates::Property<float, &ResourceData::Rarity, 13>,
    IDMTemplates::Property<bool, &ResourceData::IsRenewable, 14>,
    IDMTemplates::Property<float, &ResourceData::RespawnRate, 15>,
    IDMTemplates::Property<std::string, &ResourceData::Quality, 16>,
    IDMTemplates::Property<std::string, &ResourceData::Metadata, 17>
>;

class ResourceShard : public IDMTemplates::Shard<ResourceData, ResourceTable> {
public:
    ResourceShard(std::shared_ptr<DatabaseRouterImpl> router, const std::string& path)
    : IDMTemplates::Shard<ResourceData, ResourceTable>(router, path) {}
};
