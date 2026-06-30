// Character.cpp
#include "Character.h"
#include <sqlite3.h>


// Emscripten bindings
#ifdef EMSCRIPTEN
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(character_module) {
    class_<Health>("Health")
        .constructor()
}

EMSCRIPTEN_BINDINGS(character_module) {
    class_<Skill>("Skill")
        .constructor()
}


EMSCRIPTEN_BINDINGS(character_module) {
    class_<Character>("Character")
        .constructor()
}

#endif






