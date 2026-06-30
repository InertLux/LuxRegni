

#pragma once

#include <string>
#include <IDMTemplates.hpp>
#include <TileChunk.h> //IDMCore


//=============================================================================++++=========
// PLACE DATA
//===================++++===================================================================
struct PlaceData {
    int id = 0;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    std::string Name;
    std::string Description;
    std::string RegionPath;
    std::string PlaceType;
    float LocationX = 0.0f;
    float LocationY = 0.0f;
    float LocationZ = 0.0f;
    std::string Inhabitants;
    std::string Faction;
    bool IsDiscovered = false;
    int InhabitantCount = 0;
    std::string Metadata;
    
    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)
    IDM_PROPERTY_ACCESSORS(std::string, Name, 5)
    IDM_PROPERTY_ACCESSORS(std::string, Description, 6)
    IDM_PROPERTY_ACCESSORS(std::string, RegionPath, 7)
    IDM_PROPERTY_ACCESSORS(std::string, PlaceType, 8)
    IDM_PROPERTY_ACCESSORS(float, LocationX, 9)
    IDM_PROPERTY_ACCESSORS(float, LocationY, 10)
    IDM_PROPERTY_ACCESSORS(float, LocationZ, 11)
    IDM_PROPERTY_ACCESSORS(std::string, Inhabitants, 12)
    IDM_PROPERTY_ACCESSORS(std::string, Faction, 13)
    IDM_PROPERTY_ACCESSORS(bool, IsDiscovered, 14)
    IDM_PROPERTY_ACCESSORS(int, InhabitantCount, 15)
    IDM_PROPERTY_ACCESSORS(std::string, Metadata, 16)
};

inline constexpr IDMTemplates::ColumnDescriptor PlaceColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"},
    {"Name", "Name TEXT"},
    {"Description", "Description TEXT"},
    {"RegionPath", "RegionPath TEXT"},
    {"PlaceType", "PlaceType TEXT"},
    {"LocationX", "LocationX REAL"},
    {"LocationY", "LocationY REAL"},
    {"LocationZ", "LocationZ REAL"},
    {"Inhabitants", "Inhabitants TEXT"},
    {"Faction", "Faction TEXT"},
    {"IsDiscovered", "IsDiscovered INT"},
    {"InhabitantCount", "InhabitantCount INT"},
    {"Metadata", "Metadata TEXT"}
};

inline constexpr IDMTemplates::TableRoute PlaceRoute{
    "/{}/{Place}/{@}/{Place}",
    "RegniRecord",
    "Place",
    false,
    PlaceColumns,
    17
};

inline constexpr IDMTemplates::TableMetadata PlaceMetadata{&PlaceRoute, PlaceColumns, 17};

using PlaceTable = IDMTemplates::DataTypeImpl<
    PlaceData,
    &PlaceMetadata,
    IDMTemplates::Property<int, &PlaceData::id, 0>,
    IDMTemplates::Property<std::string, &PlaceData::path, 1>,
    IDMTemplates::Property<double, &PlaceData::Version, 2>,
    IDMTemplates::Property<std::string, &PlaceData::Flags, 3>,
    IDMTemplates::Property<std::string, &PlaceData::Tags, 4>,
    IDMTemplates::Property<std::string, &PlaceData::Name, 5>,
    IDMTemplates::Property<std::string, &PlaceData::Description, 6>,
    IDMTemplates::Property<std::string, &PlaceData::RegionPath, 7>,
    IDMTemplates::Property<std::string, &PlaceData::PlaceType, 8>,
    IDMTemplates::Property<float, &PlaceData::LocationX, 9>,
    IDMTemplates::Property<float, &PlaceData::LocationY, 10>,
    IDMTemplates::Property<float, &PlaceData::LocationZ, 11>,
    IDMTemplates::Property<std::string, &PlaceData::Inhabitants, 12>,
    IDMTemplates::Property<std::string, &PlaceData::Faction, 13>,
    IDMTemplates::Property<bool, &PlaceData::IsDiscovered, 14>,
    IDMTemplates::Property<int, &PlaceData::InhabitantCount, 15>,
    IDMTemplates::Property<std::string, &PlaceData::Metadata, 16>
>;