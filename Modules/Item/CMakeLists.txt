# Item module - same pattern for Universe, World, Region, Item, Object, Place

add_library(Item OBJECT
    Private/Item.cpp
)

target_include_directories(Item PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Public
    ${CMAKE_CURRENT_SOURCE_DIR}/Public/Types
    ${CMAKE_SOURCE_DIR}/ThirdParty/nlohmann
    ${CMAKE_SOURCE_DIR}/Modules/IDMTemplates/Public
)

set_target_properties(Item PROPERTIES CXX_STANDARD 17)

