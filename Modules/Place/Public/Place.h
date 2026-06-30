#pragma once

#include <string>
#include <IDMTemplates.hpp>
#include <TileChunk.h> //IDMCore
#include "Data/PlaceData.h"


//=============================================================================++++=========
// PLACE OBJECT (Simulation + IO)
//==============++++========================================================================

// The Collection Shard for chunks
using ChunkCollectionShard = IDMTemplates::CollectionShard<ChunkData, ChunkTable>;




// ============ PLACE WITH CHUNK COLLECTION ============

class Place : public IDMTemplates::RootObject<PlaceData, PlaceTable, ChunkCollectionShard> {
public:
    Place(std::shared_ptr<DatabaseRouterImpl> router, const std::string& objectPath)
        : RootObject(router, objectPath) {}
    
protected:

    private: 
    DatabaseRouterImpl::Target Fragment;
    std::shared_ptr<DatabaseRouterImpl> router;
};


using Place_Inst = IDMObject_Inst<Place>;

/*

Place::SaveComplete()
├─ OnSaveRootData()
│  └─ Extract PlaceData from internal state
│  └─ Route("/Place/Content/Riverrun", isWrite=true) → Shard handle
│  └─ m_definition->Save(handle, placeData)
│  └─ INSERT/UPDATE Place.Place WHERE path = '/Place/Content/Riverrun'
│
└─ SaveAllSubtypes<0>()  [ChunkCollectionShard]
   └─ SaveSubtypeAt<0>()
   └─ OnSaveSubtype<0>() returns vector of all ChunkData objects
   └─ For each chunk in collection:
      ├─ Route("/Place/Content/Riverrun/Chunk/0_0", isWrite=true) → Shard handle
      ├─ m_definition->Save(handle, chunkData)
      └─ INSERT/UPDATE Place.Chunk WHERE path = '/Place/Content/Riverrun/Chunk/0_0'
   └─ All chunks inserted with their paths intact


*/

