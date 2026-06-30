################################################################################
# Regnum - Game Instance Interface
################################################################################

add_library(Regnum OBJECT
    Private/Regnum.cpp
    Private/RegniFactory.cpp
    Private/Commands/SystemCommandModule.cpp
    Private/Commands/NavigateCommandModule.cpp
)

target_include_directories(Regnum PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Public
    ${CMAKE_CURRENT_SOURCE_DIR}/Public/Commands
    ${CMAKE_SOURCE_DIR}/Modules/IDMCore/Public
    ${CMAKE_SOURCE_DIR}/Modules/IDMCore/Public/Commands
    ${CMAKE_SOURCE_DIR}/ThirdParty/nlohmann
    ${CMAKE_SOURCE_DIR}/Modules/IDMTemplates/Public
    
    ${CMAKE_SOURCE_DIR}/Modules/IDMCore/Public
    ${CMAKE_SOURCE_DIR}/Modules/IDMTemplates/Public
    
    ${CMAKE_SOURCE_DIR}/Modules/Universe/Public
    ${CMAKE_SOURCE_DIR}/Modules/Universe/Public/Data

    ${CMAKE_SOURCE_DIR}/Modules/World/Public
    ${CMAKE_SOURCE_DIR}/Modules/World/Public/Data

    ${CMAKE_SOURCE_DIR}/Modules/Region/Public
    ${CMAKE_SOURCE_DIR}/Modules/Region/Public/Data

    ${CMAKE_SOURCE_DIR}/Modules/Place/Public
    ${CMAKE_SOURCE_DIR}/Modules/Place/Public/Data



    ${CMAKE_SOURCE_DIR}/Modules/Character/Public
    ${CMAKE_SOURCE_DIR}/Modules/Character/Public/Data

    ${CMAKE_SOURCE_DIR}/Modules/Object/Public
    ${CMAKE_SOURCE_DIR}/Modules/Object/Public/Data

    ${CMAKE_SOURCE_DIR}/Modules/Item/Public
    ${CMAKE_SOURCE_DIR}/Modules/Item/Public/Data
)
