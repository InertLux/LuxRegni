// Public/GameInstance.h

#pragma once
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <memory>
#include <string>
#include <sstream>
#include <cctype>


#include <IDMTemplates.hpp>
#include <IDMCore.h>
#include <IDMPathRouter.h>

#include "CommandRegistry.h"
#include "CommandClasses.h"

#include <Universe.h>
#include <World.h>
#include <Region.h>
#include <Place.h>
#include <Character.h>
#include <Object.h>
#include <Item.h>


#include "Commands.h"
#include <iostream>
#include <stdexcept>

#include <json.hpp>
using json = nlohmann::json;

class Regnum{
public:
    virtual ~Regnum() {}
    Regnum() {};


    static Regnum* Get() {
        static auto s_instance = std::make_unique<Regnum>();
        return s_instance.get();
    }
    static void Init(std::shared_ptr<DatabaseRouterImpl> RouterObject)
    {
        auto This = Get();
        This->Router = RouterObject;
    }

    static std::shared_ptr<DatabaseRouterImpl> GetRouter(){return Get()->Router;};

    static void CreateDataBase(const std::string& projectPath)
    {
        const std::string schemaVersion = "0.0.0.0";
        auto Router = GetRouter();
        Router->InitializeProject(projectPath, schemaVersion);
    }

    static void Register()
    {
        Universe::RegisterAllRoutes();
        Universe_Inst::Register(Regnum::LoadUniverse, Regnum::CreateUniverse, Regnum::DeleteUniverse);

        World::RegisterAllRoutes();
        World_Inst::Register(Regnum::LoadWorld, Regnum::CreateWorld, Regnum::DeleteWorld);

        Region::RegisterAllRoutes();
        Region_Inst::Register(Regnum::LoadRegion, Regnum::CreateRegion, Regnum::DeleteRegion);

        
        Place::RegisterAllRoutes();
        Place_Inst::Register(Regnum::LoadPlace, Regnum::CreatePlace, Regnum::DeletePlace);

        Character::RegisterAllRoutes();
        Character_Inst::Register(Regnum::LoadCharacter, Regnum::CreateCharacter, Regnum::DeleteCharacter);

        GameObject::RegisterAllRoutes();
        //GameObject_Inst::Register(Regnum::LoadObject, Regnum::CreateObject, Regnum::DeleteObject);

        Item::RegisterAllRoutes();
        Item_Inst::Register(Regnum::LoadItem, Regnum::CreateItem, Regnum::DeleteItem);








        GlobalCommandRegistry::RegisterModule(std::make_shared<SampleCommandModule>());
        GlobalCommandRegistry::RegisterModule(std::make_shared<NavigateCommandModule>());

        Get()->CommandBundleInst = std::make_shared<CommandBundle>();
        
        //System:
        Get()->CommandBundleInst->registerModuleForDomain(CommandBundle::CR_System, std::make_shared<SystemCommandModule>());        
        //Universe: 
        Get()->CommandBundleInst->registerModuleForDomain(CommandBundle::CR_Universe, std::make_shared<UniverseCommandModule>());


        Get()->CommandBundleInst->InjectCommands();
    }



private:
    std::shared_ptr<DatabaseRouterImpl> Router;
    
private:
    std::string ActivePackage;
    std::string TargetShard;

private:
    //Current Live Object instances.
    //Current Active Scene
    std::unordered_map<std::string, std::unique_ptr<IDMObject>> Universes;      //One of. Determining time of day and starmap, celestial events and some such

    std::unordered_map<std::string, std::unique_ptr<IDMObject>> Worlds;         //Existing in. 
    std::unordered_map<std::string, std::unique_ptr<IDMObject>> Regions;       //In and adjacent
    std::unordered_map<std::string, std::unique_ptr<IDMObject>> Places;        //As Required

    std::unordered_map<std::string, std::unique_ptr<IDMObject>> Characters;    //Many per map and cast requirements 
    std::unordered_map<std::string, std::unique_ptr<IDMObject>> Objects;       //Many
    std::unordered_map<std::string, std::unique_ptr<IDMObject>> Items;         //Many

    
public:
    std::string GetCLIPromptText()
    {
        auto Prompt = false;
        if(Prompt)
        {
            return "Input: ";
        }
        else
        {
            switch (cm_domain) {
                case CommandBundle::CommandDomain::CR_Global:     return "\033[1;37m Reg-app:\033[0m ";
                case CommandBundle::CommandDomain::CR_System:     return "\033[1;37m[Reg-sys]:\033[0m ";
                case CommandBundle::CommandDomain::CR_Universe:   return "\033[1;36m[Universe] ✦ +>\033[0m ";
                case CommandBundle::CommandDomain::CR_World:      return "\033[1;32m[World] ◈ +>\033[0m ";
                case CommandBundle::CommandDomain::CR_Region:     return "\033[1;33m[Region] ◇ +>\033[0m ";
                case CommandBundle::CommandDomain::CR_Place:      return "\033[1;35m[Place] ◆ +>\033[0m ";
                case CommandBundle::CommandDomain::CR_Character:  return "\033[1;31m[Character] ⚔ ->\033[0m ";
                case CommandBundle::CommandDomain::CR_Object:     return "\033[0;37m[Object] ⚙ ->\033[0m ";
                case CommandBundle::CommandDomain::CR_Item:       return "\033[1;34m[Item] ⬟ ->\033[0m ";
            }
        }
        return "?>";
    }

    auto& GetDomainMap(IDMCore::CoreObjects Domain) {
        switch (Domain) {
            case IDMCore::CoreObjects::IDM_Universe:  return Universes;
            case IDMCore::CoreObjects::IDM_World:     return Worlds;
            case IDMCore::CoreObjects::IDM_Region:    return Regions;
            case IDMCore::CoreObjects::IDM_Place:     return Places;
            case IDMCore::CoreObjects::IDM_Character: return Characters;
            case IDMCore::CoreObjects::IDM_Object:    return Objects;
            case IDMCore::CoreObjects::IDM_Item:      return Items;
            default: throw std::invalid_argument("Invalid domain");
        }
    }


    /*
        Resolve Object Path. 
        Search Loaded Objects for path. 
        If failed try loading from database. 
        If failed ForceCreate Create a New data entry.
    */
    IDMObject* ResolvePath(std::string Path)
    {
        //Example: std::string path = "/Package/Domain/ObjectID/Type";

        std::string Package = "";
        IDMCore::CoreObjects Domain = IDMCore::CoreObjects::IDM_None; 
        std::string ObjectPath = "";
        std::vector<std::string> FullPathArr;

        if (IDMCore::PathFromString(Path, Package, Domain, ObjectPath, FullPathArr))
        {
            try {
                IDMError::checkCondition(Domain == IDMCore::CoreObjects::IDM_None, "Unexpected Domain bit Returned From IDMCore::PathFromString @[IDMCore]/IDMCore.h)");
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << "\n";
                return nullptr;
            }


            //See if object is loaded.
            if (auto IDMObject = GetDomainMap(Domain).find(ObjectPath) != GetDomainMap(Domain).end()) {
                //DomainMap[ObjectID]->sayHello();
                
            }   
            //Try resolve from database
            else
            {
                return nullptr;
            }
        }
        return nullptr;
    }

    template <typename T>
    T* ResolvePath(std::string Path)
    {   
     //   auto Obj = ResolvePath(Path);
     //   if(auto Return* = static_cast<T>(Obj))
     //   {
     //       return Return;
     //   }
        return nullptr;
    }

    //Create a new Object in active package. 
    template <typename T>
    T* CreateObject(IDMCore::CoreObjects Domain, std::string ObjectID, bool ForceCreate = false)
    {   
       // auto Obj = ResolvePath(Path ForceCreate);
       // if(auto Return* = static_cast<T>(Obj))
       // {
       //     //Object already exists. return it.
       //     return Return;
       // }
       // else
       // {
//
       // }
        return nullptr;
    }

    void Initialize();
    
    std::string LoadScene(std::string ScenePath);

    //Per frame 
    void Update(float delta_time);
    
    
    bool GetAllRenderRelevant();
    void Shutdown();
    
    void ImportObjectAsJson(std::string ObjectPath, json Def)
    {
        // auto obj = ResolvePath(path);
        // if (!obj) {
        //     obj = ForceCreateFromPath(path);
        // }
        // if (obj) {
        //     auto typeDef = ResolveTypeDefinition(obj->GetType());
        //     if (typeDef) {
        //         typeDef->ImportJson(obj, data);
        //     }
        //     obj->SaveComplete();
        // }
    };
    void ExportObjectAsJson(std::string ObjectPath, json Def)
    {

    };
    
//====================== ARCHETYPE EDIT FUNCTIONS ======================== 
    static Universe* CreateUniverse(const std::string& Package, const std::string& Name, const json& Init = json());
    static Universe* LoadUniverse(const std::string& Path);
    static bool DeleteUniverse(const std::string& Path);

    static World* CreateWorld(const std::string& Package, const std::string& Name, const json& Init = json());
    static World* LoadWorld(const std::string& Path);
    static bool DeleteWorld(const std::string& Path);

    static Region* CreateRegion(const std::string& Package, const std::string& Name, const json& Init = json());
    static Region* LoadRegion(const std::string& Path);
    static bool DeleteRegion(const std::string& Path);

    static Place* CreatePlace(const std::string& Package, const std::string& Name, const json& Init = json());
    static Place* LoadPlace(const std::string& Path);
    static bool DeletePlace(const std::string& Path);



    static Item* CreateItem(const std::string& Package, const std::string& Name, const json& Init = json());
    static Item* LoadItem(const std::string& Path);
    static bool DeleteItem(const std::string& Path);

    static GameObject* CreateObject(const std::string& Package, const std::string& Name, const json& Init = json());
    static GameObject* LoadObject(const std::string& Path);
    static bool DeleteObject(const std::string& Path);

    static Character* CreateCharacter(const std::string& Package, const std::string& Name, const json& Init = json());
    static Character* LoadCharacter(const std::string& Path);
    static bool DeleteCharacter(const std::string& Path);

//==============================================



/*
    //generic actions. Game object types are built into path. This is for wren, casting, and dialouge.
    
    //Optionally add instance name to spawned Object.  
    //Name ID is required to be unique per object type. If it is not. This method will fail.
    virtual bool SpawnSoft(std::string Path, std::string NameID) = 0;
    
    //Optionally add instance name to spawned Object. This is important if you want to reference it later.
    //Force Spawn appends int/AutoIncrements NameID until Unique. Returns Applied NameID
    virtual std::string ForceSpawn(std::string Path, std::string NameID = "0") = 0;
    
    //Instantly move an Object to a location in a region. Resets state.
    virtual bool SetLocation(std::string Object, std::string Region, {int,int,int} Location) = 0;
    
    //Moves an object to location. with time delay to account for travel. impl diferent per entity type. Entity may or may not be added to travel pool to render display. 
    virtual bool MoveTo(std::string Object, std::string Region,std::string {int,int,int} Location) = 0;
    
    //Instantly move an Object to a location in a region. Continuous No state reset.
    virtual bool Teleport(std::string Object, std::string Region, {int,int,int} Location) = 0;
            
    //Turns character or creature to face object.
    virtual bool TurnToFace(std::string Object, std::string LookAt) = 0;
*/

private:
    std::shared_ptr<CommandBundle> CommandBundleInst;
public: 
    CommandBundle::CommandDomain cm_domain = CommandBundle::CR_Global;
public:
    CommandResult executeCommand(const std::vector<std::string>& args, std::map<std::string, std::string>& state) {
        return CommandBundleInst->executeCommand(cm_domain, args, state);
    }
};
