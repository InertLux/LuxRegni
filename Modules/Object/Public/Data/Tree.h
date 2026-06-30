#pragma once
#include <string>
#include <IDMTemplates.hpp>

struct TreeData {
    int id = 0;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    std::string Name;
    std::string Description;
    std::string RegionPath;
    std::string TreeType;
    float LocationX = 0.0f;
    float LocationY = 0.0f;
    float LocationZ = 0.0f;
    float Height = 0.0f;
    float Age = 0.0f;
    int HealthPercent = 100;
    bool CanBeHarvested = true;
    std::string HarvestableResources;
    std::string Metadata;
    
    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)
    IDM_PROPERTY_ACCESSORS(std::string, Name, 5)
    IDM_PROPERTY_ACCESSORS(std::string, Description, 6)
    IDM_PROPERTY_ACCESSORS(std::string, RegionPath, 7)
    IDM_PROPERTY_ACCESSORS(std::string, TreeType, 8)
    IDM_PROPERTY_ACCESSORS(float, LocationX, 9)
    IDM_PROPERTY_ACCESSORS(float, LocationY, 10)
    IDM_PROPERTY_ACCESSORS(float, LocationZ, 11)
    IDM_PROPERTY_ACCESSORS(float, Height, 12)
    IDM_PROPERTY_ACCESSORS(float, Age, 13)
    IDM_PROPERTY_ACCESSORS(int, HealthPercent, 14)
    IDM_PROPERTY_ACCESSORS(bool, CanBeHarvested, 15)
    IDM_PROPERTY_ACCESSORS(std::string, HarvestableResources, 16)
    IDM_PROPERTY_ACCESSORS(std::string, Metadata, 17)
};

inline constexpr IDMTemplates::ColumnDescriptor TreeColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"},
    {"Name", "Name TEXT"},
    {"Description", "Description TEXT"},
    {"RegionPath", "RegionPath TEXT"},
    {"TreeType", "TreeType TEXT"},
    {"LocationX", "LocationX REAL"},
    {"LocationY", "LocationY REAL"},
    {"LocationZ", "LocationZ REAL"},
    {"Height", "Height REAL"},
    {"Age", "Age REAL"},
    {"HealthPercent", "HealthPercent INT"},
    {"CanBeHarvested", "CanBeHarvested INT"},
    {"HarvestableResources", "HarvestableResources TEXT"},
    {"Metadata", "Metadata TEXT"}
};

inline constexpr IDMTemplates::TableRoute TreeRoute{
    "/{}/{Object}/{@}/{Tree}",
    "RegniRecord",
    "Object_Tree",
    false,
    TreeColumns, 
    18
};

inline constexpr IDMTemplates::TableMetadata TreeMetadata{&TreeRoute, TreeColumns, 18};

using TreeTable = IDMTemplates::DataTypeImpl<
    TreeData,
    &TreeMetadata,
    IDMTemplates::Property<int, &TreeData::id, 0>,
    IDMTemplates::Property<std::string, &TreeData::path, 1>,
    IDMTemplates::Property<double, &TreeData::Version, 2>,
    IDMTemplates::Property<std::string, &TreeData::Flags, 3>,
    IDMTemplates::Property<std::string, &TreeData::Tags, 4>,
    IDMTemplates::Property<std::string, &TreeData::Name, 5>,
    IDMTemplates::Property<std::string, &TreeData::Description, 6>,
    IDMTemplates::Property<std::string, &TreeData::RegionPath, 7>,
    IDMTemplates::Property<std::string, &TreeData::TreeType, 8>,
    IDMTemplates::Property<float, &TreeData::LocationX, 9>,
    IDMTemplates::Property<float, &TreeData::LocationY, 10>,
    IDMTemplates::Property<float, &TreeData::LocationZ, 11>,
    IDMTemplates::Property<float, &TreeData::Height, 12>,
    IDMTemplates::Property<float, &TreeData::Age, 13>,
    IDMTemplates::Property<int, &TreeData::HealthPercent, 14>,
    IDMTemplates::Property<bool, &TreeData::CanBeHarvested, 15>,
    IDMTemplates::Property<std::string, &TreeData::HarvestableResources, 16>,
    IDMTemplates::Property<std::string, &TreeData::Metadata, 17>
    >;


class TreeShard : public IDMTemplates::Shard<TreeData, TreeTable> {
public:
    TreeShard(std::shared_ptr<DatabaseRouterImpl> router, const std::string& path)
    : IDMTemplates::Shard<TreeData, TreeTable>(router, path) {}
};

