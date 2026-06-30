#pragma once
#include <string>
#include <IDMTemplates.hpp>

//=============================================================================++++=========
// WORLD DATA
//=============================================================================++++=========
struct WorldData {
    int id = 0;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    std::string Name;
    std::string Description;
    std::string UniversePath;
    std::string WorldType;
    float Gravity = 1.0f;
    std::string Climate;
    int RegionCount = 0;
    std::string Metadata;
    
    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)
    IDM_PROPERTY_ACCESSORS(std::string, Name, 5)
    IDM_PROPERTY_ACCESSORS(std::string, Description, 6)
    IDM_PROPERTY_ACCESSORS(std::string, UniversePath, 7)
    IDM_PROPERTY_ACCESSORS(std::string, WorldType, 8)
    IDM_PROPERTY_ACCESSORS(float, Gravity, 9)
    IDM_PROPERTY_ACCESSORS(std::string, Climate, 10)
    IDM_PROPERTY_ACCESSORS(int, RegionCount, 11)
    IDM_PROPERTY_ACCESSORS(std::string, Metadata, 12)
};

inline constexpr IDMTemplates::ColumnDescriptor WorldColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"},
    {"Name", "Name TEXT"},
    {"Description", "Description TEXT"},
    {"UniversePath", "UniversePath TEXT"},
    {"WorldType", "WorldType TEXT"},
    {"Gravity", "Gravity REAL"},
    {"Climate", "Climate TEXT"},
    {"RegionCount", "RegionCount INT"},
    {"Metadata", "Metadata TEXT"}
};
inline constexpr IDMTemplates::TableRoute WorldRoute{
    "/{}/{World}/{@}/{World}",
    "RegniRecord",
    "World",
    false,
    WorldColumns,
    13
};

inline constexpr IDMTemplates::TableMetadata WorldMetadata{&WorldRoute, WorldColumns, 13};

using WorldTable = IDMTemplates::DataTypeImpl<
    WorldData,
    &WorldMetadata,
    IDMTemplates::Property<int, &WorldData::id, 0>,
    IDMTemplates::Property<std::string, &WorldData::path, 1>,
    IDMTemplates::Property<double, &WorldData::Version, 2>,
    IDMTemplates::Property<std::string, &WorldData::Flags, 3>,
    IDMTemplates::Property<std::string, &WorldData::Tags, 4>,
    IDMTemplates::Property<std::string, &WorldData::Name, 5>,
    IDMTemplates::Property<std::string, &WorldData::Description, 6>,
    IDMTemplates::Property<std::string, &WorldData::UniversePath, 7>,
    IDMTemplates::Property<std::string, &WorldData::WorldType, 8>,
    IDMTemplates::Property<float, &WorldData::Gravity, 9>,
    IDMTemplates::Property<std::string, &WorldData::Climate, 10>,
    IDMTemplates::Property<int, &WorldData::RegionCount, 11>,
    IDMTemplates::Property<std::string, &WorldData::Metadata, 12>
>;