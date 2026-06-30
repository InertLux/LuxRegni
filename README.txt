













╔════════════════════════════════════════════════════════════════╗
║                                                                ║
║                     ██╗     ██╗   ██╗██╗  ██╗                ║
║                     ██║     ██║   ██║╚██╗██╔╝                 ║
║                     ██║     ██║   ██║ ╚███╔╝                  ║
║                     ██║     ██║   ██║ ██╔██╗                  ║
║                     ███████╗╚██████╔╝██╔╝ ██╗                 ║
║                     ╚══════╝ ╚═════╝ ╚═╝  ╚═╝                 ║
║                                                                ║
║                      ██████╗ ███████╗ ██████╗ ██╗ ██╗██╗      ║
║                      ██╔══██╗██╔════╝██╔════╝ ██║ ██║██║      ║
║                      ██████╔╝█████╗  ██║  ███╗██║ ██║██║      ║
║                      ██╔══██╗██╔══╝  ██║   ██║██║ ██║██║      ║
║                      ██║  ██║███████╗╚██████╔╝╚██████╔╝██║     ║
║                      ╚═╝  ╚═╝╚══════╝ ╚═════╝  ╚═════╝ ╚═╝     ║
║                                                                ║
║        ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━       ║
║                  Emergent World Engine v1.0                   ║
║              Multi-Database ORM Architecture                  ║
║        ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━       ║
║                                                                ║
║          some sort of descriptive text goes here               ║
║                                                                ║
╚════════════════════════════════════════════════════════════════╝


           LUX REGNI DATA 
               CORE MODULES (smpl)
       _________________________________________________________
       |             |             |             |             |             
   [👤char]      [🏰regn]      [🚪plac]      [⚔️item]      [🪑objc]
       |             |             |             |             |             
    📊stat         🗺️map        🎭npc         📦slot        🔧prop
    🎯skil         ⚔️fact       💬dial        ✨ench        🌳type
    💬hist         👥rule       🕯️lite        💰cost        🎨desc
    💰gold         🏛️lord       🎨deco        ⚖️weig        📍locn




CHAPTER START:
┌──────────────┐
│   Root DB    │  Read Only source of truth. Client copy Pulled from server. Only what target environment/Act/chapter needs.  
└──────┬───────┘
       │
       ├──→ Scene DB (read-only snapshot)
       │    - Characters unique or as archetype
       │    - Objects, as archetype
       │    - Universe, World, Region, Place. for mapping things as you need them to exist. 
       │
       └──→ Shard DB (mutable working copy)
            - Initialize state from Shard (previous chapter)
            - All runtime mutations go here
            - Character moves → update Shard
            - Dialogue choices → update Shard
            - Location transforms → update Shard

       ALL DATA CAN BE MERGED/DOWN BY DESIGN

DURING CHAPTER:
Runtime reads from Scene (immutable template)
Runtime writes to Shard (mutable state)

Shard queries like: "What's this character's current location?"
Scene queries like: "What's the character's base definition?"

CHAPTER END:
┌──────────────┐
│   Shard DB   │  All mutations from gameplay
└──────┬───────┘
       │
       └──→ Extract sticky state for next chapter

CHAPTER START (Next):
Repeat with new Shard initialized from previous Shard

The architecture employs a tripartite database structure to manage game state across narrative chapters. The Root database serves as the immutable master source, containing all canonical entity definitions, dialogue trees, and world data loaded once per chapter. The Scene database functions as a read-only snapshot derived from Root, providing the runtime system with template data—character archetypes, location blueprints, and scripted dialogue—that remain constant during gameplay. The Shard database maintains mutable state, initialized from either the previous chapter's Shard or from defaults, and accumulates all runtime mutations: character movement, inventory changes, dialogue choices, and environmental transformations. This separation ensures that queries requesting baseline definitions ("What is this character's base health?") consult Scene without contention, while queries tracking current state ("Where is this character now?") read and write exclusively to Shard.

At chapter boundaries, the Shard's accumulated state becomes the seed for the next chapter's initialization, preserving consequence and progression across narrative segments. The Scene snapshot remains static throughout a chapter, eliminating concurrency issues and allowing efficient caching of template data. This design mirrors the ludic pattern of chapters as atomic units of gameplay: each chapter receives a fixed ruleset and initial conditions from Root and Scene, operates within the constraints of Shard mutations, and closes by persisting only the delta of changes to the Shard for subsequent chapters. The pattern scales naturally to accommodate complex interdependencies—a character's current location in Shard informs which dialogue options appear in Scene, and those choices mutate Shard for future queries.

The Shard class template encapsulates a single entity type paired with its table definition, providing instance lifecycle management (Create, Destroy) and database operations (Load, Save, LoadAll, Count) that delegate to the underlying DataTypeImpl. RootObject extends this pattern to orchestrate hierarchical entity structures: a root entity type (e.g., Character) coordinates multiple Shard instances for its subtypes (e.g., Inventory, Dialogue state, Combat stats) through pack expansion and index sequences resolved at compile time. The RootObject template employs virtual hooks—OnLoadRootData, OnSaveRootData, and indexed specializations OnLoadSubtype and OnSaveSubtype—that subclasses override to define how each entity tier loads and persists. This design allows concrete entity classes to inherit from RootObject, specify their subtypes as template arguments, and implement only the hooks relevant to their composition, while the framework handles SQL generation, statement binding, and pack recursion automatically.


=====================================================================================================================================================================
Addresses, paths. 
Data objects are stored in paralell tables, each entry follows a specific path format. 
/domain/package/id/type,subtype
/Universe/Base/... I havn't figured out exactly what to put here. 
/World/Base/Earth <- meta data for entry 'Earth' in domain World for package Base.  

/Character/Base/Jeff/Character - root type data for Character in Base content package.
/Character/Base/Jeff/Character/Backpack - subtype data for Character.Backpack in Base content package.

_________________________________________________________________________________________________________________________
=========================================================================================================================
C++ Backend. 

Data Shard, Data Tables, ShardInstance objects, and RootTypeObjects.
C++ backend drives struct format and table scheme. It is a little verbose. But it allows full object encapsulation 

table type and access is infered by property details. 
so save/load can be fully encapsulated in an upstream class. 
Allowing for designers and users to focus on substance.
Type conversion can be found in Modules/IDMTemplates/Public/Conversions 
       -> It's done using template and overloading. All you have to do is add two functions for read/write  for new type.


======================================================       
ENCAPSULATED TEMPLATE OBJECT-TYPE EXAMPLE 
       -> a Root Type Class Object example for a Character Impl:
       
======================================================
struct SocialData;          using SocialTable = DataTypeImpl< .... 
struct HealthData;          using HealthTable = DataTypeImpl< .... 
struct BackpackData;        using BackpackTable = DataTypeImpl< .... 
struct CharacterData;       using CharacterTable = DataTypeImpl< .... 

                                   Shard<Type, Table>
class SocialShard : public Shard<SocialData, SocialTable> {
public:
    SocialShard() = default;
};

                                   Shard<Type, Table>
class HealthShard : public Shard<HealthData, HealthTable> {
public:
    HealthShard() = default;
};

                                   Shard<Type, Table>
class BackpackShard : public Shard<BackpackData, BackpackTable> {
public:
    BackpackShard() = default;
};

                    RootObject<Type, Table, Subtypes...>
class Character : public RootObject
<
    CharacterData,   <- Root Type 
    CharacterTable,  <- Root Type Table Def
       |
    SocialShard,     <- shard defined earlier
    HealthShard,     <- 
    BackpackShard    <- 
>  {
public:
    Character() = default;
}

==================================
 WHERE DO THE TYPES COME FROM?
 =================================
 // Backpack data
struct BackpackData {
    int id = -1;                   <- 0 REQUIRED
    std::string path = "";         <- 1
    double Version = 0.0;          <- 2
    std::string Flags;             <- 3
    std::string Tags;              <- 4 in this order

    std::string Inventory = "";    <- properties ... add as needed.

                            (type, name, member-position)
    IDM_PROPERTY_ACCESSORS(int, id, 0)
    IDM_PROPERTY_ACCESSORS(std::string, path, 1)
    IDM_PROPERTY_ACCESSORS(double, Version, 2)
    IDM_PROPERTY_ACCESSORS(std::string, Flags, 3)
    IDM_PROPERTY_ACCESSORS(std::string, Tags, 4)
    IDM_PROPERTY_ACCESSORS(std::string, Inventory, 5)
};

constexpr ColumnDescriptor BackpackColumns[] = {
    {"ID", "ID INT NOT NULL"},
    {"Path", "Path TEXT PRIMARY KEY"},
    {"Version", "Version DOUBLE NOT NULL"},
    {"Flags", "Flags TEXT"},
    {"Tags", "Tags TEXT"},
    {"Inventory", "Inventory TEXT"}
};
constexpr TableMetadata BackpackMetadata{"Character.Backpack", BackpackColumns, 6};

using BackpackTable = DataTypeImpl<
    BackpackData,           <- Type Struct
    BackpackMetadata,       <- ColumnDescriptor
    
              <type, struct-member, column-position>
    Property<int, &BackpackData::id, 0>,
    Property<std::string, &BackpackData::path, 1>,
    Property<double, &BackpackData::Version, 2>,
    Property<std::string, &BackpackData::Flags, 3>,
    Property<std::string, &BackpackData::Tags, 4>,

    Property<std::string, &BackpackData::Inventory, 5>
>;

_________________________________________________________________________________________________________________________
=========================================================================================================================
Targets.... As I develop this out I'm playing with these. 
For instance I started to add libtcod. for a ascii rougelike until I realized it's actually tilebased. 
Encripten-wasm is used for the web portal editor/simulator. 
The idea is to extract the essential dna of a game from any one dev environment. 

_________________________________________________________________________________________________________________________
=========================================================================================================================
Game Instance. I have not clarified this class just yet. 
I suppose oject instances live in map in a world. With proximity travel nodes and whatever is needed. but yea. not clarified just yet. 
Also because this was origionally entered as an acessory to game engine-scene.... 
UE5 levels... godot scenes. The form of it will just have to shape up as I make further progress. 


Universe, World, Region, Place imply an implicit heirarchy.
DB table structure is actually flat. 
It's simpler, and more knowable just to address all data by path. 
But also allows regions to change borders, for worlds to be teleported to other universes. for characters to 'move' around. whatever that actually means. 

Dialouge. Is heavily inspired by the source. By Playwriting. 
Dialouge scripts have 3 elements. 
       -> SceneList[Location, Cast, Characters, Objects] data-captures. Elements to spawn in. where scenes occur. This is the power point of abstracting game -> data. and of native data-first design   
       -> Dialouge...text interpreted, branching, goto, all that stuff.  
       -> Scripting. The Wren Scripting language is fully integrated with c++ backend allowing full OOP access to dialouge scenes. 

_________________________________________________________________________________________________________________________
=========================================================================================================================
THE SCENE DATA ABSTRACTION PROBLEM
THINGS THAT EXIST IN THE WORLD AND HOW THEY LIE ARE IT'S OWN ENCAPSULATED ARCHETYPE/ARTIFACT
=========================================================================================================================
The Scene Composite constitutes the generative authorial substrate from which all positional and volumetric instantiation derives—a parametric orchestration of procedural strata, geometric constraints, and modular compositional seeds that transform archetypal definitions into spatially coherent, visually differentiated worlds. This layer mediates between narrative intent and spatial manifestation, permitting designers to encode ecological and geographic character through deterministic generation rather than manual instantiation.

The tileset system operates as a path-addressable asset abstraction wherein each tile entry within a scene database references a composite generative seed rather than direct asset data. A tileset occupies a logical tile coordinate and maintains a path string—e.g., /Asset/Tileset/Forest/DenseVariant—that resolves through the render target's asset bundle to platform-specific geometry, texture, voxel data, or glyph representation. The tileset itself is compositionally generated: a forest seed point expands into modular tile variants (dense forest, clearing, deadwood, stone) according to deterministic noise derivatives and proximity functions, producing ecological coherence without explicit placement. Each variant is stored as a reference entry in the scene database with its computed seed state; asset resolution occurs at render time, permitting the same tile data to materialize as Minecraft blocks, Skyrim static geometry, Stardew sprites, or ASCII symbols. The path system abstracts both the logical tile identity and the asset resolution pathway, allowing scene databases to remain format-agnostic while asset bundles provide platform-specific interpretation.

The holistic system unifies three layers into a single epistemic chain: Root databases contain categorical definitions and narrative scaffolding; Scene Composites encode generative intent through seeds and constraints; Scene Layer databases instantiate computed results as spatial tile data, object placements, and asset references. A single narrative can thus generate infinite spatial variations through seed mutation while maintaining deterministic reproducibility. Render targets consume the Scene Layer as canonical positional truth, resolve asset paths to their bundled resources, and interpret tile strata according to their visual vocabulary. The entire apparatus treats the game world as a function of its seed parameters: change the seed, regenerate the scene, preserve the narrative. This inversion—data-first rather than engine-first—decouples storytelling from presentation and makes the world fungible across rendering substrates while keeping it coherent, knowable, and tractable.

The project architecture employs a hierarchical database federation wherein a single Root database (immutable, chapter-scoped, loaded once) serves as the canonical source for all archetypal entities—Characters, Items, Dialogue trees, Universe definitions—accessed through path-keyed tables with flat schema; Scene Composite databases (per World or Dimension) store generation parameters, procedural seeds, spline definitions, and tileset overlay configurations that deterministically govern spatial instantiation; Scene Layer databases (per World, Region, Dimension, or bounded narrative space) contain computed tile strata (terrain, collision, object, decoration, scripting), chunk-serialized data, NPC and item placements indexed by coordinate, and warp topology entries—all addressable via universal path strings of the form /Domain/Package/ID/Type/Subtype; a mutable Shard database (initialized per chapter from the previous chapter's delta or defaults) captures all runtime mutations (character positions, dialogue choices, inventory state, environmental transformations) scoped to the active scene, reading template data from Scene without contention; and distributed Asset databases (per render target, delivered via Steam, torrent, or CDN) provide platform-specific implementations—voxel models and textures for Minecraft, meshes and particles for Skyrim, sprites for Stardew, glyphs for ASCII—all resolved through asset URI references embedded in Scene Layer entries. The C++ backend generates SQL tables and binding code from templated struct definitions with property accessors, the Wren scripting layer permits dialogue and tile events to mutate Shard state and query any database by path, and the render target layer interprets Scene Layer tile strata and resolves asset paths to its bundled resources, producing unified narrative experience across heterogeneous visual substrates.




_________________________________________________________________________________________________________________________
=========================================================================================================================
GAME INSTANCE
OBJECT TEMPLATES AND PATH RESOLUTION. LOADING. SAVING. 
STATIC ROOT  | VS |  MUTABLE SHARD 
=========================================================================================================================
DatabaseRouter Interface
Router answers one question: which database owns this path, and is it writable? Callers register routing rules at startup—/Character/.* → Shard (writable), /World/Base/.* → Scene (read-only)—and attach sqlite3 handles. When Shard needs to Load or Save, it calls Route(path, isWrite). Router regex-matches the path, enforces write protection (throws if you try to write read-only), resolves the handle, returns RouteResult. Shard and RootObject never ask what database lives where. They provide a path and a direction. Router handles the rest. Add a new override database or split Root across files? Register the rules, attach the handles. Logic stays clean.

Data Shard
Every game object lives at a path: /Character/Base/Jeff/Character, /World/Base/Earth/Metadata. Root database loads once at chapter start—immutable archive of all canonical data. Shard database holds mutable runtime state, initialized from previous chapter's delta plus Root defaults. Queries split by intent: read static definition from Root, read or write current state to Shard. DatabaseRouter routes each path to the correct database and enforces access rules. Root and Scene are read-only. Shard is writable. When Shard calls Load() or Save(), it queries the router, gets back the sqlite3 handle, and proceeds. No caller needs to know or care which database owns what.

Root Object
RootObject handles hierarchical entities. A Character declares subtypes as template arguments—HealthShard, BackpackShard, SocialShard. Framework builds each subtype's path automatically, routes it through the same dispatcher, and unpacks all shards in sequence at LoadComplete() and SaveComplete(). At chapter end, only delta persists—final state minus Root defaults. Next chapter reinitializes Shard with that delta plus new Root. If Jeff lost an arm, that fact travels forward.

SQLite* Database 
    Provided By Router. 
    Determined by path.
    Targets one of: [Root, Base, Shard] Inferred by intent.

Table Scheme:
/domain/package/id <- meta info about this entry. currently unused.

/domain/package/id/type <- base type ->  SELECT * FROM "Character.Character" WHERE path = '/Character/Base/Jeff/Character'
/domain/package/id/Subtype <- Subtype ->  SELECT * FROM "Character.Backpack" WHERE path = '/Character/Base/Jeff/Backpack'


// ============ DATABASE ROUTER INTERFACE ============
/*
The Router stands as the IO path resolution between Target Instance, and data backend (wherever it is physically stored.)
Following the tripartite 'Fragment' Structure of Root, Base, Shard. The Database Fragment exists in degrees of duplicated state. this is fully intentional As The need to have a single point of truth, an understandable canvas, then following emergent story state and other 'Temporal' changes. This is a Delta forward approach that 'merges' changes heirarchally. 
 In this way tranmission of mutations is very cheap. though at some performance cost. 
The lifecycle of this class is expected to be fully managed by User Target specific Game Instance. It is an interface, only because System FilePath IO will need to be specific to platform. 
*/
// ============ DATABASE ROUTER INTERFACE ============


_________________________________________________________________________________________________________________________
=========================================================================================================================
GAME INSTANCE
SCENE SPOOLING AND CAST CREATION. 
=========================================================================================================================

CHAPTER START
    ↓
Root DB: Tables "Character.Character", "Character.Health", "Character.Backpack", etc.
    ↓
Shard DB: Same table schema, initialized from [delta] + [Root defaults]
    ↓
Character Jeff loads
    ├─ Route /Character/Base/Jeff/Character → Shard
    │  └─ SELECT * FROM "Character.Character" WHERE path = '/Character/Base/Jeff/Character'
    ├─ Route /Character/Base/Jeff/Health → Shard
    │  └─ SELECT * FROM "Character.Health" WHERE path = '/Character/Base/Jeff/Health'
    ├─ Route /Character/Base/Jeff/Backpack → Shard
    │  └─ SELECT * FROM "Character.Backpack" WHERE path = '/Character/Base/Jeff/Backpack'
    └─ Route /Character/Base/Jeff/Social → Shard
       └─ SELECT * FROM "Character.Social" WHERE path = '/Character/Base/Jeff/Social'
    ↓
GAMEPLAY: mutations accumulate in Shard
    ├─ Jeff takes damage
    │  └─ UPDATE "Character.Health" WHERE path = '/Character/Base/Jeff/Health' SET hp = 45
    ├─ Jeff moves
    │  └─ INSERT/UPDATE "Character.Position" WHERE path = '/Character/Base/Jeff/Position' SET location = '...'
    └─ Jeff chooses dialogue
       └─ UPDATE "Character.Social" WHERE path = '/Character/Base/Jeff/Social' SET last_choice = 3
    ↓
CHAPTER END
    ├─ SaveComplete() writes all Shard rows
    ├─ Delta: compare each Shard row to Root row by path
    │  └─ Differences persisted; identical rows discarded
    └─ Next chapter reloads Shard from [persisted delta] + [new Root]
    ↓
NEXT CHAPTER START
    - Shard reinitialized with [previous delta] + [new Root defaults]
    - Jeff appears with one arm (if he lost it) because delta persisted
    - New story elements become available/unavailable based on delta state
