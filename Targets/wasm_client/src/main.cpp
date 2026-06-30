#include <emscripten/bind.h>
#include <iostream>
#include <string>
#include <memory>
#include <nlohmann/json.hpp>

#include "WrenEngine.h"
#include "Character.h"
#include "Item.h"
#include "Object.h"
#include "Place.h"
#include "Region.h"
#include "Universe.h"
#include "World.h"

using json = nlohmann::json;

class Program {

public:
  Program(){}
  

  ~Program() = default;

};
