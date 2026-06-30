#pragma once

#include <string>
#include <IDMTemplates.hpp>

struct ChestData {
    int id = 0;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    std::string Name;
    std::string Description;
    std::string RegionPath;
    float LocationX = 0.0f;
    float LocationY = 0.0f;
    float LocationZ = 0.0f;
    int Capacity = 0;
    int CurrentLoad = 0;
    bool IsLocked = false;
    std::string LockDifficulty;
    std::string Contents;
    std::string Owner;
    std::string Metadata;
    
    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)
    IDM_PROPERTY_ACCESSORS(std::string, Name, 5)
    IDM_PROPERTY_ACCESSORS(std::string, Description, 6)
    IDM_PROPERTY_ACCESSORS(std::string, RegionPath, 7)
    IDM_PROPERTY_ACCESSORS(float, LocationX, 8)
    IDM_PROPERTY_ACCESSORS(float, LocationY, 9)
    IDM_PROPERTY_ACCESSORS(float, LocationZ, 10)
    IDM_PROPERTY_ACCESSORS(int, Capacity, 11)
    IDM_PROPERTY_ACCESSORS(int, CurrentLoad, 12)
    IDM_PROPERTY_ACCESSORS(bool, IsLocked, 13)
    IDM_PROPERTY_ACCESSORS(std::string, LockDifficulty, 14)
    IDM_PROPERTY_ACCESSORS(std::string, Contents, 15)
    IDM_PROPERTY_ACCESSORS(std::string, Owner, 16)
    IDM_PROPERTY_ACCESSORS(std::string, Metadata, 17)
};

inline constexpr IDMTemplates::ColumnDescriptor ChestColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"},
    {"Name", "Name TEXT"},
    {"Description", "Description TEXT"},
    {"RegionPath", "RegionPath TEXT"},
    {"LocationX", "LocationX REAL"},
    {"LocationY", "LocationY REAL"},
    {"LocationZ", "LocationZ REAL"},
    {"Capacity", "Capacity INT"},
    {"CurrentLoad", "CurrentLoad INT"},
    {"IsLocked", "IsLocked INT"},
    {"LockDifficulty", "LockDifficulty TEXT"},
    {"Contents", "Contents TEXT"},
    {"Owner", "Owner TEXT"},
    {"Metadata", "Metadata TEXT"}
};

inline constexpr IDMTemplates::TableRoute ChestRoute{
    "/{}/{Object}/{@}/{Chest}",
    "RegniRecord",
    "Object_Chest",
    false,
    ChestColumns,
    18
};

inline constexpr IDMTemplates::TableMetadata ChestMetadata{&ChestRoute, ChestColumns, 18};

using ChestTable = IDMTemplates::DataTypeImpl<
    ChestData,
    &ChestMetadata,
    IDMTemplates::Property<int, &ChestData::id, 0>,
    IDMTemplates::Property<std::string, &ChestData::path, 1>,
    IDMTemplates::Property<double, &ChestData::Version, 2>,
    IDMTemplates::Property<std::string, &ChestData::Flags, 3>,
    IDMTemplates::Property<std::string, &ChestData::Tags, 4>,
    IDMTemplates::Property<std::string, &ChestData::Name, 5>,
    IDMTemplates::Property<std::string, &ChestData::Description, 6>,
    IDMTemplates::Property<std::string, &ChestData::RegionPath, 7>,
    IDMTemplates::Property<float, &ChestData::LocationX, 8>,
    IDMTemplates::Property<float, &ChestData::LocationY, 9>,
    IDMTemplates::Property<float, &ChestData::LocationZ, 10>,
    IDMTemplates::Property<int, &ChestData::Capacity, 11>,
    IDMTemplates::Property<int, &ChestData::CurrentLoad, 12>,
    IDMTemplates::Property<bool, &ChestData::IsLocked, 13>,
    IDMTemplates::Property<std::string, &ChestData::LockDifficulty, 14>,
    IDMTemplates::Property<std::string, &ChestData::Contents, 15>,
    IDMTemplates::Property<std::string, &ChestData::Owner, 16>,
    IDMTemplates::Property<std::string, &ChestData::Metadata, 17>
>;

class ChestShard : public IDMTemplates::Shard<ChestData, ChestTable> {
public:
        ChestShard(std::shared_ptr<DatabaseRouterImpl> router, const std::string& path)
        : IDMTemplates::Shard<ChestData, ChestTable>(router, path) {}
};
