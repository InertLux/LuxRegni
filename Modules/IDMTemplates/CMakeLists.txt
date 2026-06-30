# IDMTemplates module - Base templates only (no concrete types)

add_library(IDMTemplates STATIC
    Private/IDMPathRouter.cpp
    Private/IDMTypes.cpp
)

target_include_directories(IDMTemplates PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Public
    ${CMAKE_SOURCE_DIR}/ThirdParty/sqlite3
    ${CMAKE_SOURCE_DIR}/ThirdParty/nlohmann
)

set_target_properties(IDMTemplates PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if(MSVC)
    target_compile_options(IDMTemplates PRIVATE /W4)
else()
    target_compile_options(IDMTemplates PRIVATE -Wall -Wextra -Wpedantic)
endif()
