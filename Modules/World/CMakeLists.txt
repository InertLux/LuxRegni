# World module - same pattern for Universe, World, Region, Item, Object, Place

add_library(World OBJECT
    Private/World.cpp
)


target_include_directories(World PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Public
    ${CMAKE_SOURCE_DIR}/ThirdParty/nlohmann
    ${CMAKE_SOURCE_DIR}/Modules/IDMTemplates/Public
)

set_target_properties(World PROPERTIES CXX_STANDARD 17)

