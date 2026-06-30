#include "Regnum.h"


    void Regnum::Initialize(){};
    
    //Per frame 
    void Regnum::Update(float delta_time){};
    
    
    bool Regnum::GetAllRenderRelevant(){return true;};

    void Regnum::Shutdown(){};




//====================== ARCHETYPE EDIT FUNCTIONS ======================== 

    Universe* Regnum::CreateUniverse(const std::string& Package, const std::string& Name, const json& Init)
    {
        std::string path = "/" + Package + "/Universe/" + Name;
        auto route = Get()->GetRouter()->Route(path, true);
        if (!route.writable) return nullptr;    

        auto universe = std::make_unique<Universe>(Get()->GetRouter(), path);
        universe->ImportAllJson(Init);
        universe->SaveAll();

        auto ptr = universe.get();
        Get()->Universes[Name] = std::move(universe);
        return ptr;
    }   

    Universe* Regnum::LoadUniverse(const std::string& Path)
    {
        auto& map = Get()->Universes;
        auto it = map.find(Path);
        if (it != map.end()) return dynamic_cast<Universe*>(it->second.get());

        auto universe = std::make_unique<Universe>(Get()->GetRouter(), Path);
        auto ptr = universe.get();
        map[Path] = std::move(universe);
        return ptr;
    }   

    bool Regnum::DeleteUniverse(const std::string& Path)
    {
        auto& map = Get()->Universes;
        auto it = map.find(Path);
        if (it != map.end()) {
        //    it->second->Delete();
            map.erase(it);
            return true;
        }
        return false;
    }


    World* Regnum::CreateWorld(const std::string& Package, const std::string& Name, const json& Init)
{
    std::string path = "/" + Package + "/World/" + Name;
    auto route = Get()->GetRouter()->Route(path, true);
    if (!route.writable) return nullptr;

    auto world = std::make_unique<World>(Get()->GetRouter(), path);
    world->ImportAllJson(Init);
    world->SaveAll();
    
    auto ptr = world.get();
    Get()->Worlds[Name] = std::move(world);
    return ptr;
}

World* Regnum::LoadWorld(const std::string& Path)
{
    auto& map = Get()->Worlds;
    auto it = map.find(Path);
    if (it != map.end()) return dynamic_cast<World*>(it->second.get());
    
    auto world = std::make_unique<World>(Get()->GetRouter(), Path);
    auto ptr = world.get();
    map[Path] = std::move(world);
    return ptr;
}

bool Regnum::DeleteWorld(const std::string& Path)
{
    auto& map = Get()->Worlds;
    auto it = map.find(Path);
    if (it != map.end()) {
    //    it->second->Delete();
        map.erase(it);
        return true;
    }
    return false;
}

Region* Regnum::CreateRegion(const std::string& Package, const std::string& Name, const json& Init)
{
    std::string path = "/" + Package + "/Region/" + Name;
    auto route = Get()->GetRouter()->Route(path, true);
    if (!route.writable) return nullptr;

    auto region = std::make_unique<Region>(Get()->GetRouter(), path);
    region->ImportAllJson(Init);
    region->SaveAll();
    
    auto ptr = region.get();
    Get()->Regions[Name] = std::move(region);
    return ptr;
}

Region* Regnum::LoadRegion(const std::string& Path)
{
    auto& map = Get()->Regions;
    auto it = map.find(Path);
    if (it != map.end()) return dynamic_cast<Region*>(it->second.get());
    
    auto region = std::make_unique<Region>(Get()->GetRouter(), Path);
    auto ptr = region.get();
    map[Path] = std::move(region);
    return ptr;
}

bool Regnum::DeleteRegion(const std::string& Path)
{
    auto& map = Get()->Regions;
    auto it = map.find(Path);
    if (it != map.end()) {
    //    it->second->Delete();
        map.erase(it);
        return true;
    }
    return false;
}

Place* Regnum::CreatePlace(const std::string& Package, const std::string& Name, const json& Init)
{
    std::string path = "/" + Package + "/Place/" + Name;
    auto route = Get()->GetRouter()->Route(path, true);
    if (!route.writable) return nullptr;

    auto place = std::make_unique<Place>(Get()->GetRouter(), path);
    place->ImportAllJson(Init);
    place->SaveAll();
    
    auto ptr = place.get();
    Get()->Places[Name] = std::move(place);
    return ptr;
}

Place* Regnum::LoadPlace(const std::string& Path)
{
    auto& map = Get()->Places;
    auto it = map.find(Path);
    if (it != map.end()) return dynamic_cast<Place*>(it->second.get());
    
    auto place = std::make_unique<Place>(Get()->GetRouter(), Path);
    auto ptr = place.get();
    map[Path] = std::move(place);
    return ptr;
}

bool Regnum::DeletePlace(const std::string& Path)
{
    auto& map = Get()->Places;
    auto it = map.find(Path);
    if (it != map.end()) {
    //    it->second->Delete();
        map.erase(it);
        return true;
    }
    return false;
}

Item* Regnum::CreateItem(const std::string& Package, const std::string& Name, const json& Init)
{
    std::string path = "/" + Package + "/Item/" + Name;
    auto route = Get()->GetRouter()->Route(path, true);
    if (!route.writable) return nullptr;

    auto item = std::make_unique<Item>(Get()->GetRouter(), path);
    item->ImportAllJson(Init);
    item->SaveAll();
    
    auto ptr = item.get();
    Get()->Items[Name] = std::move(item);
    return ptr;
}

Item* Regnum::LoadItem(const std::string& Path)
{
    auto& map = Get()->Items;
    auto it = map.find(Path);
    if (it != map.end()) return dynamic_cast<Item*>(it->second.get());
    
    auto item = std::make_unique<Item>(Get()->GetRouter(), Path);
    auto ptr = item.get();
    map[Path] = std::move(item);
    return ptr;
}

bool Regnum::DeleteItem(const std::string& Path)
{
    auto& map = Get()->Items;
    auto it = map.find(Path);
    if (it != map.end()) {
    //    it->second->Delete();
        map.erase(it);
        return true;
    }
    return false;
}

GameObject* Regnum::CreateObject(const std::string& Package, const std::string& Name, const json& Init)
{
    std::string path = "/" + Package + "/Object/" + Name;
    auto route = Get()->GetRouter()->Route(path, true);
    if (!route.writable) return nullptr;

    auto object = std::make_unique<GameObject>(Get()->GetRouter(), path);
    object->ImportAllJson(Init);
    object->SaveAll();
    
    auto ptr = object.get();
    Get()->Objects[Name] = std::move(object);
    return ptr;
}

GameObject* Regnum::LoadObject(const std::string& Path)
{
    auto& map = Get()->Objects;
    auto it = map.find(Path);
    if (it != map.end()) return dynamic_cast<GameObject*>(it->second.get());
    
    auto object = std::make_unique<GameObject>(Get()->GetRouter(), Path);
    auto ptr = object.get();
    map[Path] = std::move(object);
    return ptr;
}

bool Regnum::DeleteObject(const std::string& Path)
{
    auto& map = Get()->Objects;
    auto it = map.find(Path);
    if (it != map.end()) {
    //    it->second->Delete();
        map.erase(it);
        return true;
    }
    return false;
}

Character* Regnum::CreateCharacter(const std::string& Package, const std::string& Name, const json& Init)
{
    std::string path = "/" + Package + "/Character/" + Name;
    auto route = Get()->GetRouter()->Route(path, true);
    if (!route.writable) return nullptr;

    auto character = std::make_unique<Character>(Get()->GetRouter(), path);
    character->ImportAllJson(Init);
    character->SaveAll();
    
    auto ptr = character.get();
    Get()->Characters[Name] = std::move(character);
    return ptr;
}

Character* Regnum::LoadCharacter(const std::string& Path)
{
    auto& map = Get()->Characters;
    auto it = map.find(Path);
    if (it != map.end()) return dynamic_cast<Character*>(it->second.get());
    
    auto character = std::make_unique<Character>(Get()->GetRouter(), Path);
    auto ptr = character.get();
    map[Path] = std::move(character);
    return ptr;
}

bool Regnum::DeleteCharacter(const std::string& Path)
{
    auto& map = Get()->Characters;
    auto it = map.find(Path);
    if (it != map.end()) {
    //    it->second->Delete();
        map.erase(it);
        return true;
    }
    return false;
}

//======================  ========================