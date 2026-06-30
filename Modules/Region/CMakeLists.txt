# Region module - same pattern for Universe, World, Region, Item, Object, Place

add_library(Region OBJECT
    Private/Region.cpp
)

target_include_directories(Region PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Public
    ${CMAKE_SOURCE_DIR}/ThirdParty/nlohmann
    ${CMAKE_SOURCE_DIR}/Modules/IDMTemplates/Public
)

set_target_properties(Region PROPERTIES CXX_STANDARD 17)

