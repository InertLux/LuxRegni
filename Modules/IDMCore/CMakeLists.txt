# IDMCore module - same pattern for Universe, World, Region, Item, Object, Place


# IDMCore module
add_library(IDMCore STATIC
    Private/IDMCore.cpp
)

target_include_directories(IDMCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Public
    ${CMAKE_SOURCE_DIR}/ThirdParty/sqlite3
    ${CMAKE_SOURCE_DIR}/ThirdParty/nlohmann
)

set_target_properties(IDMCore PROPERTIES CXX_STANDARD 17)
