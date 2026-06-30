#pragma once

#include <string>
#include <IDMTemplates.hpp>


namespace IDMError
{
    inline void checkCondition(bool condition, const std::string& message) {
        if (!condition) {
            throw std::runtime_error(message);
        }
    }
};



namespace IDMCore
{

    enum CoreObjects
    {
        IDM_None,
        IDM_Universe,
        IDM_World,
        IDM_Region,
        IDM_Place,

        IDM_Character,
        IDM_Object,
        IDM_Item
    };

    //returns true if a valid object path. 
    inline bool PathFromString(const std::string& InputString, std::string& Package, CoreObjects& Domain, std::string& ObjectPath, std::vector<std::string>& FullPathArr)
    {
        //Example: std::string path = "/Package/Domain/ObjectID/Type";
        std::string lowerPath = "";

        for (char c : InputString) {
            lowerPath += std::tolower(c);
        }

        std::vector<std::string> parts;

        // Split the string by '/' and collect non-empty parts
        std::stringstream ss(lowerPath);
        std::string part;
        while (std::getline(ss, part, '/')) {
            if (!part.empty()) {
                parts.push_back(part);
            }
        }

        if (parts.size() >= 3)
        {
            if (parts[1] == "universe") Domain = IDM_Universe;
            else if (parts[1] == "world") Domain = IDM_World;
            else if (parts[1] == "region") Domain = IDM_Region;
            else if (parts[1] == "place") Domain = IDM_Place;
            
            else if (parts[1] == "character") Domain = IDM_Character;
            else if (parts[1] == "object") Domain = IDM_Object;
            else if (parts[1] == "item") Domain = IDM_Item;
            else return false;

            //out
            FullPathArr = parts;
            Package = parts[0];
            ObjectPath = "/" + parts[0] + "/" + parts[1] + "/" + parts[2];
        
            return true;
        }

        return false;
    }
};



