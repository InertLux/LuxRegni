#pragma once
#include <IDMTemplates.hpp>


//=============================================================================++++=========
// UNIVERSE DATA
//=============================================================================++++=========
struct UniverseData {
    int id = 0;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    std::string Name;
    std::string Description;
    std::string CreationDate;

    int WorldCount = 0;
    std::string Metadata;
    std::string WorldPaths;

    //Dimensions... small self encapsulated scenes that exists in the nowhere.
    std::string DimensionPaths;

    //Dimensions... Special path dimension linking 'warp points' existing in the nowhere.
    std::string SkelterWayPaths;

    //World Gates...
    std::string GatePaths;


    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)

    IDM_PROPERTY_ACCESSORS(std::string, Name, 5)
    IDM_PROPERTY_ACCESSORS(std::string, Description, 6)
    IDM_PROPERTY_ACCESSORS(std::string, CreationDate, 7)

    IDM_PROPERTY_ACCESSORS(int, WorldCount, 8)
    IDM_PROPERTY_ACCESSORS(std::string, Metadata, 9)
};

inline constexpr IDMTemplates::ColumnDescriptor UniverseColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"},
    {"Name", "Name TEXT"},
    {"Description", "Description TEXT"},
    {"CreationDate", "CreationDate TEXT"},
    {"WorldCount", "WorldCount INT"},
    {"Metadata", "Metadata TEXT"}
};

inline constexpr IDMTemplates::TableRoute UniverseRoute{
    "/{}/{Universe}/{@}/{Universe}",
    "RegniRecord",
    "Universe",
    false,
    UniverseColumns,
    10
};

inline constexpr IDMTemplates::TableMetadata UniverseMetadata{&UniverseRoute, UniverseColumns, 10};

using UniverseTable = IDMTemplates::DataTypeImpl<
    UniverseData,
    &UniverseMetadata,
    IDMTemplates::Property<int, &UniverseData::id, 0>,
    IDMTemplates::Property<std::string, &UniverseData::path, 1>,
    IDMTemplates::Property<double, &UniverseData::Version, 2>,
    IDMTemplates::Property<std::string, &UniverseData::Flags, 3>,
    IDMTemplates::Property<std::string, &UniverseData::Tags, 4>,
    IDMTemplates::Property<std::string, &UniverseData::Name, 5>,
    IDMTemplates::Property<std::string, &UniverseData::Description, 6>,
    IDMTemplates::Property<std::string, &UniverseData::CreationDate, 7>,
    IDMTemplates::Property<int, &UniverseData::WorldCount, 8>,
    IDMTemplates::Property<std::string, &UniverseData::Metadata, 9>
>;
