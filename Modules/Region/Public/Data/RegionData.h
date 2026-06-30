#pragma once
#include <string>
#include <IDMTemplates.hpp>


//=============================================================================++++=========
// REGION DATA
//=============================================================================++++=========
struct RegionData {
    int id = 0;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    std::string Name;
    std::string Description;
    std::string WorldPath;
    std::string Terrain;
    std::string BiomeType;
    int PopulationCount = 0;
    std::string GovernmentType;
    int PlaceCount = 0;
    std::string Metadata;
    
    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)
    IDM_PROPERTY_ACCESSORS(std::string, Name, 5)
    IDM_PROPERTY_ACCESSORS(std::string, Description, 6)
    IDM_PROPERTY_ACCESSORS(std::string, WorldPath, 7)
    IDM_PROPERTY_ACCESSORS(std::string, Terrain, 8)
    IDM_PROPERTY_ACCESSORS(std::string, BiomeType, 9)
    IDM_PROPERTY_ACCESSORS(int, PopulationCount, 10)
    IDM_PROPERTY_ACCESSORS(std::string, GovernmentType, 11)
    IDM_PROPERTY_ACCESSORS(int, PlaceCount, 12)
    IDM_PROPERTY_ACCESSORS(std::string, Metadata, 13)
};

inline constexpr IDMTemplates::ColumnDescriptor RegionColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"},
    {"Name", "Name TEXT"},
    {"Description", "Description TEXT"},
    {"WorldPath", "WorldPath TEXT"},
    {"Terrain", "Terrain TEXT"},
    {"BiomeType", "BiomeType TEXT"},
    {"PopulationCount", "PopulationCount INT"},
    {"GovernmentType", "GovernmentType TEXT"},
    {"PlaceCount", "PlaceCount INT"},
    {"Metadata", "Metadata TEXT"}
};

inline constexpr IDMTemplates::TableRoute RegionRoute{
    "/{}/{Region}/{@}/{Region}",
    "RegniRecord",
    "Region",
    false,
    RegionColumns,
    14
};
inline constexpr IDMTemplates::TableMetadata RegionMetadata{&RegionRoute, RegionColumns, 14};

using RegionTable = IDMTemplates::DataTypeImpl<
    RegionData,
    &RegionMetadata,
    IDMTemplates::Property<int, &RegionData::id, 0>,
    IDMTemplates::Property<std::string, &RegionData::path, 1>,
    IDMTemplates::Property<double, &RegionData::Version, 2>,
    IDMTemplates::Property<std::string, &RegionData::Flags, 3>,
    IDMTemplates::Property<std::string, &RegionData::Tags, 4>,
    IDMTemplates::Property<std::string, &RegionData::Name, 5>,
    IDMTemplates::Property<std::string, &RegionData::Description, 6>,
    IDMTemplates::Property<std::string, &RegionData::WorldPath, 7>,
    IDMTemplates::Property<std::string, &RegionData::Terrain, 8>,
    IDMTemplates::Property<std::string, &RegionData::BiomeType, 9>,
    IDMTemplates::Property<int, &RegionData::PopulationCount, 10>,
    IDMTemplates::Property<std::string, &RegionData::GovernmentType, 11>,
    IDMTemplates::Property<int, &RegionData::PlaceCount, 12>,
    IDMTemplates::Property<std::string, &RegionData::Metadata, 13>
>;