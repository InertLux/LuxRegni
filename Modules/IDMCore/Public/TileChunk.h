#pragma once 

#include <string>
#include <IDMTemplates.hpp>


//=============================================================================++++=========
// WORLD CHUNK DATA
//=============================================================================++++=========
struct WorldChunkData {
    
    // Chunk identity
    int32_t id;                     // Primary identifier
    std::string path;               // /World/Base/Earth/Chunk_0_0
    int32_t chunkX, chunkY;
    


    /*
        World Chunk.
        Stores macro raster maps. biome, faction-territory maps, flow maps, more as needed. 
        This is the Highest abstraction layer for scene data. 


    */

    
    // Metadata
    uint64_t generationSeed;        // For reproducibility
    double version;

    IDM_PROPERTY_ACCESSORS(int32_t, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(int32_t, chunkX, 2)
    IDM_PROPERTY_ACCESSORS(int32_t, chunkY, 3)

    

    IDM_PROPERTY_ACCESSORS(uint64_t, generationSeed, 10)
    IDM_PROPERTY_ACCESSORS(double, version, 11)
};


//=============================================================================++++=========
// REGION CHUNK DATA
//=============================================================================++++=========
struct RegionChunkData {
    
    // Chunk identity
    int32_t id;                     // Primary identifier
    std::string path;               // /World/Base/Earth/Chunk_0_0
    int32_t chunkX, chunkY;
    


    /*
        Regions have chunk collection... 
        but also each chunk has metadata. 
        this stores the metadata..
        
        Think of it as a macro layer for local overlays.  flow
                    map, heightmaps, Travel path nodes ect. 

        World also has it's own layers. 

        it's all compositional favoring the smallest element. 

    */

    
    // Metadata
    uint64_t generationSeed;        // For reproducibility
    double version;

    IDM_PROPERTY_ACCESSORS(int32_t, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(int32_t, chunkX, 2)
    IDM_PROPERTY_ACCESSORS(int32_t, chunkY, 3)



    IDM_PROPERTY_ACCESSORS(uint64_t, generationSeed, 10)
    IDM_PROPERTY_ACCESSORS(double, version, 11)
};

inline constexpr IDMTemplates::ColumnDescriptor RegionChunkColumns[] = {
    {"ID", "ID INT PRIMARY KEY"},
    {"Path", "Path TEXT NOT NULL"},
    {"ChunkX", "ChunkX INT NOT NULL"},
    {"ChunkY", "ChunkY INT NOT NULL"},


    {"GenerationSeed", "GenerationSeed INTEGER NOT NULL"},
    {"Version", "Version DOUBLE NOT NULL"}
};


inline constexpr IDMTemplates::TableRoute RegionChunkRoute{
    "/{}/{Region}/{$}/{Chunks}/{@}",
    "RegniRecord",
    "$",
    true,
    RegionChunkColumns,
    12
};

inline constexpr IDMTemplates::TableMetadata RegionChunkMetadata{&RegionChunkRoute, RegionChunkColumns, 12};

using RegionChunkTable = IDMTemplates::DataTypeImpl<
    RegionChunkData,
    &RegionChunkMetadata,
    IDMTemplates::Property<int32_t, &RegionChunkData::id, 0>,
    IDMTemplates::Property<std::string, &RegionChunkData::path, 1>,
    IDMTemplates::Property<int32_t, &RegionChunkData::chunkX, 2>,
    IDMTemplates::Property<int32_t, &RegionChunkData::chunkY, 3>,


    IDMTemplates::Property<uint64_t, &RegionChunkData::generationSeed, 10>,
    IDMTemplates::Property<double, &RegionChunkData::version, 11>
>;


//=============================================================================++++=========
// CHUNK DATA
//=============================================================================++++=========
struct ChunkData {
    
    // Chunk identity
    int32_t id;                     // Primary identifier
    std::string path;               // /World/Base/Earth/Chunk_0_0
    int32_t chunkX, chunkY;
    int32_t width, height;
    int32_t depthLayers;

    /*
        This is the tiledata layer. 
        The lowest and largest data layer.

        Map interpretation is highly compositional.
        Every place has it's data chunks. 

        Every place loads in schematics of tileset scenes.
        In sequence of render priority...
        
        data is loaded-streamed on demmand and used as needed.
    */
    
    // Single flat array: [depth * height * width]
    // Each uint64_t encodes: tileDefID (16b) + rotation (3b) + flags (8b) + pathIndex (16b) + instanceData (21b)
    std::string tileDataBase64;     // Compressed serialization of uint64_t[]
    
    // Tile path lookup table (CSV or JSON)
    // Maps pathIndex (0-65535) → "/Asset/Tileset/Forest/DenseVariant"
    std::string participatingTilePaths;  // CSV: "0,/Asset/Tileset/Forest/DenseVariant\n1,/Asset/Tileset/Forest/Clearing\n..."
    
    // Per-tile instance data (for chests, doors, NPCs, etc.)
    // Key: "x_y_depth", Value: JSON object
    std::string instanceDataJSON;   // {"0_5_0": {"type": "Chest", "inventory": [...]}, ...}
    
    // Metadata
    uint64_t generationSeed;        // For reproducibility
    double version;

    IDM_PROPERTY_ACCESSORS(int32_t, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(int32_t, chunkX, 2)
    IDM_PROPERTY_ACCESSORS(int32_t, chunkY, 3)
    IDM_PROPERTY_ACCESSORS(int32_t, width, 4)
    IDM_PROPERTY_ACCESSORS(int32_t, height, 5)
    IDM_PROPERTY_ACCESSORS(int32_t, depthLayers, 6)
    IDM_PROPERTY_ACCESSORS(std::string, tileDataBase64, 7)
    IDM_PROPERTY_ACCESSORS(std::string, participatingTilePaths, 8)
    IDM_PROPERTY_ACCESSORS(std::string, instanceDataJSON, 9)
    IDM_PROPERTY_ACCESSORS(uint64_t, generationSeed, 10)
    IDM_PROPERTY_ACCESSORS(double, version, 11)
};

inline constexpr IDMTemplates::ColumnDescriptor ChunkColumns[] = {
    {"ID", "ID INT PRIMARY KEY"},
    {"Path", "Path TEXT NOT NULL"},
    {"ChunkX", "ChunkX INT NOT NULL"},
    {"ChunkY", "ChunkY INT NOT NULL"},
    {"Width", "Width INT NOT NULL"},
    {"Height", "Height INT NOT NULL"},
    {"DepthLayers", "DepthLayers INT NOT NULL"},
    {"TileDataBase64", "TileDataBase64 TEXT NOT NULL"},
    {"ParticipatingTilePaths", "ParticipatingTilePaths TEXT NOT NULL"},
    {"InstanceDataJSON", "InstanceDataJSON TEXT"},
    {"GenerationSeed", "GenerationSeed INTEGER NOT NULL"},
    {"Version", "Version DOUBLE NOT NULL"}
};


inline constexpr IDMTemplates::TableRoute ChunkRoute{
    "/{}/{Place}/{$}/{Chunks}/{@}",
    "RegniRecord",
    "$",
    true,
    ChunkColumns,
    12
};


inline constexpr IDMTemplates::TableMetadata ChunkMetadata{&ChunkRoute, ChunkColumns, 12};

using ChunkTable = IDMTemplates::DataTypeImpl<
    ChunkData,
    &ChunkMetadata,
    IDMTemplates::Property<int32_t, &ChunkData::id, 0>,
    IDMTemplates::Property<std::string, &ChunkData::path, 1>,
    IDMTemplates::Property<int32_t, &ChunkData::chunkX, 2>,
    IDMTemplates::Property<int32_t, &ChunkData::chunkY, 3>,
    IDMTemplates::Property<int32_t, &ChunkData::width, 4>,
    IDMTemplates::Property<int32_t, &ChunkData::height, 5>,
    IDMTemplates::Property<int32_t, &ChunkData::depthLayers, 6>,
    IDMTemplates::Property<std::string, &ChunkData::tileDataBase64, 7>,
    IDMTemplates::Property<std::string, &ChunkData::participatingTilePaths, 8>,
    IDMTemplates::Property<std::string, &ChunkData::instanceDataJSON, 9>,
    IDMTemplates::Property<uint64_t, &ChunkData::generationSeed, 10>,
    IDMTemplates::Property<double, &ChunkData::version, 11>
>;
