#pragma once
#include <string>
#include <IDMTemplates.hpp>
struct PickaxeData {
    int id = 0;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)
};

inline constexpr IDMTemplates::ColumnDescriptor PickaxeColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"}
};
inline constexpr IDMTemplates::TableRoute PickaxeRoute{
    "/{}/{Item}/{@}/{Pickaxe}",
    "RegniRecord",
    "Item_Pickaxe",
    false,
    PickaxeColumns,
    5
};
inline constexpr IDMTemplates::TableMetadata PickaxeMetadata{&PickaxeRoute, PickaxeColumns, 5};

using PickaxeTable = IDMTemplates::DataTypeImpl<
    PickaxeData,
    &PickaxeMetadata,
    IDMTemplates::Property<int, &PickaxeData::id, 0>,
    IDMTemplates::Property<std::string, &PickaxeData::path, 1>,
    IDMTemplates::Property<double, &PickaxeData::Version, 2>,
    IDMTemplates::Property<std::string, &PickaxeData::Flags, 3>,
    IDMTemplates::Property<std::string, &PickaxeData::Tags, 4>
>;




struct AxeData {
    int id = 0;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)
};

inline constexpr IDMTemplates::ColumnDescriptor AxeColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"}
};
inline constexpr IDMTemplates::TableRoute AxeRoute{
    "/{}/{Item}/{@}/{Axe}",
    "RegniRecord",
    "Item_Axe",
    false,
    AxeColumns,
    5
};
inline constexpr IDMTemplates::TableMetadata AxeMetadata{&AxeRoute, AxeColumns, 5};

using AxeTable = IDMTemplates::DataTypeImpl<
    AxeData,
    &AxeMetadata,
    IDMTemplates::Property<int, &AxeData::id, 0>,
    IDMTemplates::Property<std::string, &AxeData::path, 1>,
    IDMTemplates::Property<double, &AxeData::Version, 2>,
    IDMTemplates::Property<std::string, &AxeData::Flags, 3>,
    IDMTemplates::Property<std::string, &AxeData::Tags, 4>
>;



struct HoeData {
    int id = 0;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)
};

inline constexpr IDMTemplates::ColumnDescriptor HoeColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"}
};
inline constexpr IDMTemplates::TableRoute HoeRoute{
    "/{}/{Item}/{@}/{Hoe}",
    "RegniRecord",
    "Item_Hoe",
    false,
    HoeColumns,
    5
};
inline constexpr IDMTemplates::TableMetadata HoeMetadata{&HoeRoute, HoeColumns, 5};

using HoeTable = IDMTemplates::DataTypeImpl<
    HoeData,
    &HoeMetadata,
    IDMTemplates::Property<int, &HoeData::id, 0>,
    IDMTemplates::Property<std::string, &HoeData::path, 1>,
    IDMTemplates::Property<double, &HoeData::Version, 2>,
    IDMTemplates::Property<std::string, &HoeData::Flags, 3>,
    IDMTemplates::Property<std::string, &HoeData::Tags, 4>
>;



struct BucketData {
    int id = 0;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)
};

inline constexpr IDMTemplates::ColumnDescriptor BucketColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"}
};
inline constexpr IDMTemplates::TableRoute BucketRoute{
    "/{}/{Item}/{@}/{Bucket}",
    "RegniRecord",
    "Item_Bucket",
    false,
    BucketColumns,
    5
};
inline constexpr IDMTemplates::TableMetadata BucketMetadata{&BucketRoute, BucketColumns, 5};

using BucketTable = IDMTemplates::DataTypeImpl<
    BucketData,
    &BucketMetadata,
    IDMTemplates::Property<int, &BucketData::id, 0>,
    IDMTemplates::Property<std::string, &BucketData::path, 1>,
    IDMTemplates::Property<double, &BucketData::Version, 2>,
    IDMTemplates::Property<std::string, &BucketData::Flags, 3>,
    IDMTemplates::Property<std::string, &BucketData::Tags, 4>
>;



struct ShovelData {
    int id = 0;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)
};

inline constexpr IDMTemplates::ColumnDescriptor ShovelColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"}
};
inline constexpr IDMTemplates::TableRoute ShovelRoute{
    "/{}/{Item}/{@}/{Shovel}",
    "RegniRecord",
    "Item_Shovel",
    false,
    ShovelColumns,
    5
};

inline constexpr IDMTemplates::TableMetadata ShovelMetadata{&ShovelRoute, ShovelColumns, 5};

using ShovelTable = IDMTemplates::DataTypeImpl<
    ShovelData,
    &ShovelMetadata,
    IDMTemplates::Property<int, &ShovelData::id, 0>,
    IDMTemplates::Property<std::string, &ShovelData::path, 1>,
    IDMTemplates::Property<double, &ShovelData::Version, 2>,
    IDMTemplates::Property<std::string, &ShovelData::Flags, 3>,
    IDMTemplates::Property<std::string, &ShovelData::Tags, 4>
>;




struct SickleData {
    int id = 0;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)
};

inline constexpr IDMTemplates::ColumnDescriptor SickleColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"}
};
inline constexpr IDMTemplates::TableRoute SickleRoute{
    "/{}/{Item}/{@}/{Sickle}",
    "RegniRecord",
    "Item_Sickle",
    false,
    SickleColumns,
    5
};

inline constexpr IDMTemplates::TableMetadata SickleMetadata{&SickleRoute, SickleColumns, 5};

using SickleTable = IDMTemplates::DataTypeImpl<
    SickleData,
    &SickleMetadata,
    IDMTemplates::Property<int, &SickleData::id, 0>,
    IDMTemplates::Property<std::string, &SickleData::path, 1>,
    IDMTemplates::Property<double, &SickleData::Version, 2>,
    IDMTemplates::Property<std::string, &SickleData::Flags, 3>,
    IDMTemplates::Property<std::string, &SickleData::Tags, 4>
>;





