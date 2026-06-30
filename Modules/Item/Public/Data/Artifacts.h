#pragma once
#include <string>
#include <IDMTemplates.hpp>

struct GrenadeData {
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

inline constexpr IDMTemplates::ColumnDescriptor GrenadeColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"}
};

inline constexpr IDMTemplates::TableRoute GrenadeRoute{
    "/{}/{Item}/{@}/{Grenade}",
    "RegniRecord",
    "Item_Grenade",
    false,
    GrenadeColumns,
    5
};

inline constexpr IDMTemplates::TableMetadata GrenadeMetadata{&GrenadeRoute, GrenadeColumns, 5};

using GrenadeTable = IDMTemplates::DataTypeImpl<
    GrenadeData,
    &GrenadeMetadata,
    IDMTemplates::Property<int, &GrenadeData::id, 0>,
    IDMTemplates::Property<std::string, &GrenadeData::path, 1>,
    IDMTemplates::Property<double, &GrenadeData::Version, 2>,
    IDMTemplates::Property<std::string, &GrenadeData::Flags, 3>,
    IDMTemplates::Property<std::string, &GrenadeData::Tags, 4>
>;

    class GrenadeShard : public IDMTemplates::Shard<GrenadeData, GrenadeTable> {
    public:
        GrenadeShard(std::shared_ptr<DatabaseRouterImpl> router, const std::string& path)
        : IDMTemplates::Shard<GrenadeData, GrenadeTable>(router, path) {}
    };


struct TurretData {
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

inline constexpr IDMTemplates::ColumnDescriptor TurretColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"}
};

inline constexpr IDMTemplates::TableRoute TurretRoute{
    "/{}/{Item}/{@}/{Turret}",
    "RegniRecord",
    "Item_Turret",
    false,
    TurretColumns,
    5
};

inline constexpr IDMTemplates::TableMetadata TurretMetadata{&TurretRoute, TurretColumns, 5};

using TurretTable = IDMTemplates::DataTypeImpl<
    TurretData,
    &TurretMetadata,
    IDMTemplates::Property<int, &TurretData::id, 0>,
    IDMTemplates::Property<std::string, &TurretData::path, 1>,
    IDMTemplates::Property<double, &TurretData::Version, 2>,
    IDMTemplates::Property<std::string, &TurretData::Flags, 3>,
    IDMTemplates::Property<std::string, &TurretData::Tags, 4>
>;

    class TurretShard : public IDMTemplates::Shard<TurretData, TurretTable> {
    public:
        TurretShard(std::shared_ptr<DatabaseRouterImpl> router, const std::string& path)
        : IDMTemplates::Shard<TurretData, TurretTable>(router, path) {}
    };


struct AutomatonData {
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

inline constexpr IDMTemplates::ColumnDescriptor AutomatonColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"}
};
inline constexpr IDMTemplates::TableRoute AutomatonRoute{
    "/{}/{Item}/{@}/{Automaton}",
    "RegniRecord",
    "Item_Automaton",
    false,
    AutomatonColumns,
    5
};
inline constexpr IDMTemplates::TableMetadata AutomatonMetadata{&AutomatonRoute, AutomatonColumns, 5};

using AutomatonTable = IDMTemplates::DataTypeImpl<
    AutomatonData,
    &AutomatonMetadata,
    IDMTemplates::Property<int, &AutomatonData::id, 0>,
    IDMTemplates::Property<std::string, &AutomatonData::path, 1>,
    IDMTemplates::Property<double, &AutomatonData::Version, 2>,
    IDMTemplates::Property<std::string, &AutomatonData::Flags, 3>,
    IDMTemplates::Property<std::string, &AutomatonData::Tags, 4>
>;


    class AutomatonShard : public IDMTemplates::Shard<AutomatonData, AutomatonTable> {
    public:
        AutomatonShard(std::shared_ptr<DatabaseRouterImpl> router, const std::string& path)
        : IDMTemplates::Shard<AutomatonData, AutomatonTable>(router, path) {}
    };


struct ConveyorData {
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

inline constexpr IDMTemplates::ColumnDescriptor ConveyorColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"}
};
inline constexpr IDMTemplates::TableRoute ConveyorRoute{
    "/{}/{Item}/{@}/{Conveyor}",
    "RegniRecord",
    "Item_Conveyor",
    false,
    ConveyorColumns,
    5
};
inline constexpr IDMTemplates::TableMetadata ConveyorMetadata{&ConveyorRoute, ConveyorColumns, 5};

using ConveyorTable = IDMTemplates::DataTypeImpl<
    ConveyorData,
    &ConveyorMetadata,
    IDMTemplates::Property<int, &ConveyorData::id, 0>,
    IDMTemplates::Property<std::string, &ConveyorData::path, 1>,
    IDMTemplates::Property<double, &ConveyorData::Version, 2>,
    IDMTemplates::Property<std::string, &ConveyorData::Flags, 3>,
    IDMTemplates::Property<std::string, &ConveyorData::Tags, 4>
>;    


    class ConveyorShard : public IDMTemplates::Shard<ConveyorData, ConveyorTable> {
    public:
        ConveyorShard(std::shared_ptr<DatabaseRouterImpl> router, const std::string& path)
        : IDMTemplates::Shard<ConveyorData, ConveyorTable>(router, path) {}
    };

