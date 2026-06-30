################################################################################
# WASM Client Target (Temporalis - Web)
################################################################################

if(NOT EMSCRIPTEN)
    message(FATAL_ERROR "WASM target requires Emscripten")
endif()

add_executable(luxregni_client
    Private/main.cpp
)

target_link_libraries(luxregni_client PUBLIC 
    LuxRegni
    embind
)
target_link_options(luxregni_client PRIVATE
    "SHELL:-s WASM=1"
    "SHELL:-s ALLOW_MEMORY_GROWTH=1"
    "SHELL:-s EXPORTED_RUNTIME_METHODS=['ccall','cwrap']"
    "SHELL:--bind"
)
