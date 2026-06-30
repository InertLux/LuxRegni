#pragma once

#include <string>
#include <IDMTemplates.hpp>




// Health data
struct ItemData {

    int id = 0;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;


    std::string Name;
    std::string Description;
    float Weight;
    float Value;
    std::string Essence;
    std::string Friends;

    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)

    IDM_PROPERTY_ACCESSORS(std::string, Name, 5)
    IDM_PROPERTY_ACCESSORS(std::string, Description, 6)
    IDM_PROPERTY_ACCESSORS(float, Weight, 7)
    IDM_PROPERTY_ACCESSORS(float, Value, 8)
    IDM_PROPERTY_ACCESSORS(std::string, Essence, 9)
    IDM_PROPERTY_ACCESSORS(std::string, Friends, 10)
};




// Character (root)
inline constexpr IDMTemplates::ColumnDescriptor ItemColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"},

    {"Name", "Name TEXT"},
    {"Description", "Description TEXT"},
    {"Weight", "Weight DOUBLE"},
    {"Value", "Value DOUBLE"},
    {"Essence", "Essence TEXT"},
    {"Friends", "Friends TEXT"},
};

inline constexpr IDMTemplates::TableRoute ItemRoute{
    "/{}/{Item}/{@}/{Item}",
    "RegniRecord",
    "Item",
    false,
    ItemColumns,
    11
};

inline constexpr IDMTemplates::TableMetadata ItemMetadata{&ItemRoute, ItemColumns, 11};

using ItemTable = IDMTemplates::DataTypeImpl<
    ItemData,
    &ItemMetadata,
    IDMTemplates::Property<int, &ItemData::id, 0>,
    IDMTemplates::Property<std::string, &ItemData::path, 1>,
    IDMTemplates::Property<double, &ItemData::Version, 2>,
    IDMTemplates::Property<std::string, &ItemData::Flags, 3>,
    IDMTemplates::Property<std::string, &ItemData::Tags, 4>,

    IDMTemplates::Property<std::string, &ItemData::Name, 5>,
    IDMTemplates::Property<std::string, &ItemData::Description, 6>,
    IDMTemplates::Property<float, &ItemData::Weight, 7>,
    IDMTemplates::Property<float, &ItemData::Value, 8>,
    IDMTemplates::Property<std::string, &ItemData::Essence, 9>,
    IDMTemplates::Property<std::string, &ItemData::Friends, 10>
>;