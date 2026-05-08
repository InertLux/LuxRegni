# Core library
add_library(gameBackend SHARED
    core/world.cpp
    core/entity.cpp
    persistence/database.cpp
    api/public_api.cpp
)

# Public header
target_include_directories(gameBackend PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# Internal headers
target_include_directories(gameBackend PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../third_party
)

# Obfuscation flags
target_compile_options(gameBackend PRIVATE
    -fvisibility=hidden
    -fvisibility-inlines-hidden
    -Os
)

if(WIN32)
    target_link_options(gameBackend PRIVATE /STRIP)
elseif(UNIX)
    # Strip symbols after build
    add_custom_command(TARGET gameBackend POST_BUILD
        COMMAND strip -s $<TARGET_FILE:gameBackend>
        COMMENT "Stripping debug symbols..."
    )
endif()

# SQLite3
find_package(SQLite3 REQUIRED)
target_link_libraries(gameBackend PRIVATE SQLite::SQLite3)

# Optional: JSON library (header-only)
target_include_directories(gameBackend PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/nlohmann
)
