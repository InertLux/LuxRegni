#pragma once

#include <string>
#include <IDMTemplates.hpp>




struct FoodData {
    int id = 0;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    int Calories = 0;
    std::string Effect;
    float EffectPotency = 0.0f;

    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)
    IDM_PROPERTY_ACCESSORS(int, Calories, 5)
    IDM_PROPERTY_ACCESSORS(std::string, Effect, 6)
    IDM_PROPERTY_ACCESSORS(float, EffectPotency, 7)
};

inline constexpr IDMTemplates::ColumnDescriptor FoodColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"},
    {"Calories", "Calories INT"},
    {"Effect", "Effect TEXT"},
    {"EffectPotency", "EffectPotency FLOAT"}
};
inline constexpr IDMTemplates::TableRoute FoodRoute{
    "/{}/{Item}/{@}/{Food}",
    "RegniRecord",
    "Item_Food",
    false,
    FoodColumns,
    8
};
inline constexpr IDMTemplates::TableMetadata FoodMetadata{&FoodRoute, FoodColumns, 8};

using FoodTable = IDMTemplates::DataTypeImpl<
    FoodData,
    &FoodMetadata,
    IDMTemplates::Property<int, &FoodData::id, 0>,
    IDMTemplates::Property<std::string, &FoodData::path, 1>,
    IDMTemplates::Property<double, &FoodData::Version, 2>,
    IDMTemplates::Property<std::string, &FoodData::Flags, 3>,
    IDMTemplates::Property<std::string, &FoodData::Tags, 4>,
    IDMTemplates::Property<int, &FoodData::Calories, 5>,
    IDMTemplates::Property<std::string, &FoodData::Effect, 6>,
    IDMTemplates::Property<float, &FoodData::EffectPotency, 7>
>;

class FoodShard : public IDMTemplates::Shard<FoodData, FoodTable> {
public:
        FoodShard(std::shared_ptr<DatabaseRouterImpl> router, const std::string& path)
        : IDMTemplates::Shard<FoodData, FoodTable>(router, path) {}
};

struct SalveData {
    int id = 0;
    std::string path = "";
    double Version = 0.0;
    std::string Flags;
    std::string Tags;

    std::string Effect;
    std::string Targets;

    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)
    IDM_PROPERTY_ACCESSORS(std::string, Effect, 5)
    IDM_PROPERTY_ACCESSORS(std::string, Targets, 6)
};

inline constexpr IDMTemplates::ColumnDescriptor SalveColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"},
    {"Effect", "Effect TEXT"},
    {"Targets", "Targets TEXT"}
};
inline constexpr IDMTemplates::TableRoute SalveRoute{
    "/{}/{Item}/{@}/{Salve}",
    "RegniRecord",
    "Item_Salve",
    false,
    SalveColumns,
    7
};
inline constexpr IDMTemplates::TableMetadata SalveMetadata{&SalveRoute, SalveColumns, 7};

using SalveTable = IDMTemplates::DataTypeImpl<
    SalveData,
    &SalveMetadata,
    IDMTemplates::Property<int, &SalveData::id, 0>,
    IDMTemplates::Property<std::string, &SalveData::path, 1>,
    IDMTemplates::Property<double, &SalveData::Version, 2>,
    IDMTemplates::Property<std::string, &SalveData::Flags, 3>,
    IDMTemplates::Property<std::string, &SalveData::Tags, 4>,
    IDMTemplates::Property<std::string, &SalveData::Effect, 5>,
    IDMTemplates::Property<std::string, &SalveData::Targets, 6>
>;


class SalveShard : public IDMTemplates::Shard<SalveData, SalveTable> {
public:
        SalveShard(std::shared_ptr<DatabaseRouterImpl> router, const std::string& path)
        : IDMTemplates::Shard<SalveData, SalveTable>(router, path) {}
};

struct IngredientData {
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

inline constexpr IDMTemplates::ColumnDescriptor IngredientColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"}
};

inline constexpr IDMTemplates::TableRoute IngredientRoute{
    "/{}/{Item}/{@}/{Ingredient}",
    "RegniRecord",
    "Item_Ingredient",
    false,
    IngredientColumns,
    5
};

inline constexpr IDMTemplates::TableMetadata IngredientMetadata{&IngredientRoute, IngredientColumns, 5};

using IngredientTable = IDMTemplates::DataTypeImpl<
    IngredientData,
    &IngredientMetadata,
    IDMTemplates::Property<int, &IngredientData::id, 0>,
    IDMTemplates::Property<std::string, &IngredientData::path, 1>,
    IDMTemplates::Property<double, &IngredientData::Version, 2>,
    IDMTemplates::Property<std::string, &IngredientData::Flags, 3>,
    IDMTemplates::Property<std::string, &IngredientData::Tags, 4>
>;



class IngredientShard : public IDMTemplates::Shard<IngredientData, IngredientTable> {
public:
        IngredientShard(std::shared_ptr<DatabaseRouterImpl> router, const std::string& path)
        : IDMTemplates::Shard<IngredientData, IngredientTable>(router, path) {}
};

