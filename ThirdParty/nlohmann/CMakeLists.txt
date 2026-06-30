# JSON module - nlohmann/json wrapper/interface

add_library(JSON INTERFACE)

target_include_directories(JSON INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/ThirdParty/nlohmann_json/include
)

set_target_properties(JSON PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
