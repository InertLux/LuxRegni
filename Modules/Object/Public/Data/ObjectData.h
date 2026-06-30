
#pragma once
#include <string>
#include <IDMTemplates.hpp>
#include <sqlite3.h>
#include <memory>
#include <unordered_map>
#include <string>




struct GameObjectData {
    int id = 0;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    std::string Name;
    
    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)

    IDM_PROPERTY_ACCESSORS(std::string, Name, 5)
};

inline constexpr IDMTemplates::ColumnDescriptor GameObjectColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"},
    
    {"Name", "Name TEXT"}
};

inline constexpr IDMTemplates::TableRoute ObjectRoute{
    "/{}/{Object}/{@}/{Object}",
    "RegniRecord",
    "Object",
    false,
    GameObjectColumns,
    6
};

inline constexpr IDMTemplates::TableMetadata GameObjectMetadata{&ObjectRoute, GameObjectColumns, 6};

using GameObjectTable = IDMTemplates::DataTypeImpl<
    GameObjectData,
    &GameObjectMetadata,
    IDMTemplates::Property<int, &GameObjectData::id, 0>,
    IDMTemplates::Property<std::string, &GameObjectData::path, 1>,
    IDMTemplates::Property<double, &GameObjectData::Version, 2>,
    IDMTemplates::Property<std::string, &GameObjectData::Flags, 3>,
    IDMTemplates::Property<std::string, &GameObjectData::Tags, 4>,

    IDMTemplates::Property<std::string, &GameObjectData::Name, 5>
>;