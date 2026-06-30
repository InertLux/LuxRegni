#pragma once
#include <string>
#include <IDMTemplates.hpp>


struct ComposedChunk {
    int32_t chunkX, chunkY;
    int32_t width, height;          // In logical tiles
    int32_t depthLayers = 0;        // Number of Z-levels (1 for 2D, N for 3D)
    
    // Single canonical tile grid: [depth][y][x]
    std::vector<std::vector<std::vector<uint32_t>>> tileGrid;
    
    // Metadata packed into tile ID
    struct TileMetadata {
        uint16_t tileDefID;         // Index into tile definition table
        uint8_t rotation;           // 0-3 for cardinal; 0-7 for octants
        uint8_t flags;              // Walkable, collides, opaque, etc.
        uint8_t reserved;           // For future use
    };
    // tileGrid[d][y][x] = packed as: (TileMetadata*)&u32
    
    // Optional: cache render-target-specific data
    struct RenderCache {
        std::string assetPathsJSON;  // Resolved asset paths (cached)
        uint64_t buildSeed;          // For invalidation
    } cache;
};





class IRenderTarget {
public:
    virtual ~IRenderTarget() = default;
    
    // Resolve tile definition to platform-specific data
    struct TileDefinition {
        uint16_t id;
        std::string path;           // e.g., /Asset/Tileset/Forest/DenseVariant
        std::string assetBundle;    // Which bundle defines this tile
        std::map<std::string, std::string> metadata;  // {key: value}
    };
    
    virtual TileDefinition ResolveTileDefID(uint16_t tileDefID) = 0;
    
    // Render a composed chunk
    // The compositor output (canonical tile grid) is passed in; 
    // render target interprets it for its own engine
    virtual void RenderChunk(const ComposedChunk& chunk) = 0;
    
    // Query capabilities
    virtual int GetMaxDepthLayers() = 0;
    virtual bool SupportsRotation() = 0;
    virtual int GetRotationGranularity() = 0;  // 4 or 8
};




class ASCIIRenderTarget : public IRenderTarget {
private:
    // Tile definition table (loaded at startup from root database)
    std::map<uint16_t, TileDefinition> tileDefCache;
    
    // ASCII glyph mapping (hardcoded or loaded from tile defs)
    std::map<uint16_t, char> tileToGlyph = {
        {1, '.'},   // Grass
        {2, '#'},   // Stone
        {3, '~'},   // Water
        {4, 'T'},   // Tree
        // ... etc
    };
    
public:
    TileDefinition ResolveTileDefID(uint16_t tileDefID) override {
        if (tileDefCache.count(tileDefID)) {
            return tileDefCache[tileDefID];
        }
        
        // Load from root database
        auto tileRow = rootDB->Query(
            "SELECT id, path, metadata FROM TileDefs WHERE id = ?",
            tileDefID
        );
        
        TileDefinition def;
        def.id = tileDefID;
        def.path = tileRow.path;
        def.assetBundle = "ASCII";
        def.metadata["glyph"] = tileToGlyph[tileDefID];
        
        tileDefCache[tileDefID] = def;
        return def;
    }
    
    void RenderChunk(const ComposedChunk& chunk) override {
        // Only use depth layer 0 (top layer)
        const auto& layer = chunk.tileGrid[0];
        
        std::string output;
        for (int y = 0; y < chunk.height; ++y) {
            for (int x = 0; x < chunk.width; ++x) {
                uint32_t packedTile = layer[y][x];
                uint16_t tileDefID = ExtractTileDefID(packedTile);
                
                char glyph = tileToGlyph[tileDefID];
                output += glyph;
            }
            output += "\n";
        }
        
        std::cout << output;
    }
    
    int GetMaxDepthLayers() override { return 1; }
    bool SupportsRotation() override { return false; }
    int GetRotationGranularity() override { return 0; }
};
