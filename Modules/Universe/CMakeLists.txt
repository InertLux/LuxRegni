# Universe module - same pattern for Universe, World, Region, Item, Object, Place

add_library(Universe OBJECT
    Private/Universe.cpp
)

target_include_directories(Universe PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Public
    ${CMAKE_SOURCE_DIR}/ThirdParty/nlohmann
    ${CMAKE_SOURCE_DIR}/Modules/IDMTemplates/Public
    ${CMAKE_SOURCE_DIR}/Modules/IDMCore/Public
)

set_target_properties(Universe PROPERTIES CXX_STANDARD 17)

