# Character module - same pattern for Universe, World, Region, Item, Object, Place


add_library(Character OBJECT
    Private/Character.cpp

)

target_include_directories(Character PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Public
    ${CMAKE_SOURCE_DIR}/ThirdParty/sqlite3
    ${CMAKE_SOURCE_DIR}/ThirdParty/nlohmann
    ${CMAKE_SOURCE_DIR}/Modules/IDMTemplates/Public
)

set_target_properties(Character PROPERTIES CXX_STANDARD 17)

