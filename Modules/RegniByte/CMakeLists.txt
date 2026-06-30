################################################################################
# RegniByte Module
################################################################################

add_library(RegniByte OBJECT
    Private/RegniByte.cpp
    Private/AsciiScene.cpp
    Private/Editors/AsciiTableEditor.cpp
    
    Private/Render/RaylibPresenter.cpp
)

target_include_directories(RegniByte PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Public
    ${CMAKE_CURRENT_SOURCE_DIR}/Public/Editors
    ${CMAKE_CURRENT_SOURCE_DIR}/Public/Render
    
    ${CMAKE_SOURCE_DIR}/ThirdParty/raylib/src
    ${CMAKE_SOURCE_DIR}/ThirdParty/cimgui
    
    ${CMAKE_SOURCE_DIR}/ThirdParty/nlohmann
    ${CMAKE_SOURCE_DIR}/Modules/IDMTemplates/Public
)

target_include_directories(RegniByte PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Private
    ${CMAKE_CURRENT_SOURCE_DIR}/Private/Render
)

target_compile_features(RegniByte PUBLIC cxx_std_17)

target_link_libraries(RegniByte PUBLIC raylib cimgui_raylib)

if(MSVC)
    target_compile_options(RegniByte PRIVATE /W4)
else()
    target_compile_options(RegniByte PRIVATE -Wall -Wextra -Wpedantic)
endif()
