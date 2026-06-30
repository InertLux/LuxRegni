# Object module - same pattern for Universe, World, Region, Item, Object, Place

add_library(Object OBJECT
    Private/Object.cpp
)



target_include_directories(Object PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Public
    ${CMAKE_SOURCE_DIR}/ThirdParty/nlohmann
    ${CMAKE_SOURCE_DIR}/Modules/IDMTemplates/Public
)



set_target_properties(Object PROPERTIES CXX_STANDARD 17)

