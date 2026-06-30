# Place module - same pattern for Universe, World, Region, Item, Object, Place

add_library(Place OBJECT
    Private/Place.cpp
)

target_include_directories(Place PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Public
    ${CMAKE_SOURCE_DIR}/ThirdParty/nlohmann
    ${CMAKE_SOURCE_DIR}/Modules/IDMTemplates/Public
    ${CMAKE_SOURCE_DIR}/Modules/IDMCore/Public
)


set_target_properties(Place PROPERTIES CXX_STANDARD 17)

