# cmake_minimum_required(VERSION 3.21)
# project(FlappyBird C CXX)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # vcpkg makes these work flawlessly
# find_package(Freetype REQUIRED)
# find_package(glm CONFIG REQUIRED)
# find_package(SDL2 CONFIG REQUIRED) # Since you installed sdl2 via vcpkg as well

# add_executable(${PROJECT_NAME} 
#     src/main.cpp
#     src/glad.c 
#     src/Application.cpp
#     src/stb_image.cpp
#     src/Shader.cpp
#     src/Collision.cpp
#     src/Bird.cpp
#     src/InputManager.cpp
#     src/Pillar.cpp
#     src/Pillars.cpp
#     src/PillarPair.cpp
#     src/TextRenderer.cpp
#     src/Button.cpp
#     src/Menu.cpp
# )

# target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++ -static)
# # target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++ -static)

# target_include_directories(${PROJECT_NAME} PRIVATE 
#     ${CMAKE_CURRENT_SOURCE_DIR}/include
# )

# target_link_libraries(${PROJECT_NAME} PRIVATE
#     Freetype::Freetype
#     glm::glm
#     SDL2::SDL2main
#     SDL2::SDL2      
#     opengl32
# )

# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different 
#         $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> 
#         $<TARGET_FILE_DIR:${PROJECT_NAME}>
#     COMMAND_EXPAND_LISTS
# )


cmake_minimum_required(VERSION 3.21)
project(FlappyBird C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==============================================================================
# Build Configuration & Options
# ==============================================================================

# Set a default build type to "Release" if none is specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build (Debug, Release, RelWithDebInfo, MinSizeRel)." FORCE)
endif()
message(STATUS "Current Build Type: ${CMAKE_BUILD_TYPE}")

# Option to toggle AddressSanitizer (Default OFF)
option(ENABLE_ASAN "Enable AddressSanitizer for memory debugging" OFF)

# ==============================================================================
# Dependencies & Targets
# ==============================================================================

find_package(Freetype REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)


add_executable(${PROJECT_NAME}  WIN32
    src/main.cpp
    src/glad.c 
    src/Application.cpp
    src/stb_image.cpp
    src/Shader.cpp
    src/Collision.cpp
    src/Bird.cpp
    src/InputManager.cpp
    src/Pillar.cpp
    src/Pillars.cpp
    src/PillarPair.cpp
    src/TextRenderer.cpp
    src/Button.cpp
    src/Menu.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link the libraries that are the same on both OSs
target_link_libraries(${PROJECT_NAME} PRIVATE
    Freetype::Freetype
    glm::glm
    SDL2::SDL2main
    SDL2::SDL2  
)


# Link the correct OS-specific OpenGL library
if(WIN32)
    # This runs when you use your MinGW cross-compiler
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
else()
    # This runs when you use your native Linux compiler
    target_link_libraries(${PROJECT_NAME} PRIVATE GL)
endif()

# ==============================================================================
# Linker & Compiler Flags
# ==============================================================================

if(ENABLE_ASAN)
    message(STATUS "ASan ENABLED: Disabling static linking for compatibility.")
    
    # ASan requires debug symbols (-g) and frame pointers to give useful crash logs
    target_compile_options(${PROJECT_NAME} PRIVATE 
        -fsanitize=address 
        -fno-omit-frame-pointer 
        -g
    )
    target_link_options(${PROJECT_NAME} PRIVATE 
        -fsanitize=address
    )
else()
    message(STATUS "ASan DISABLED: Statically linking standard libraries.")
    
    # Statically link compiler libraries for easy distribution
    target_link_options(${PROJECT_NAME} PRIVATE 
        -static-libgcc 
        -static-libstdc++ 
        -static  #comment if you want to test with valgrind
    )
endif()

# ==============================================================================
# Post-Build DLL Copying
# ==============================================================================

# 1. Copy Dependency DLLs (SDL2, Freetype, etc. from vcpkg)
if(DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED VCPKG_TARGET_TRIPLET)
    # Traverse back from the vcpkg.cmake toolchain file to find the root vcpkg folder
    get_filename_component(VCPKG_ROOT_DIR "${CMAKE_TOOLCHAIN_FILE}" DIRECTORY)
    get_filename_component(VCPKG_ROOT_DIR "${VCPKG_ROOT_DIR}/../.." ABSOLUTE)
    
    # Point to the correct folder based on the Build Type
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(VCPKG_BIN_DIR "${VCPKG_ROOT_DIR}/installed/${VCPKG_TARGET_TRIPLET}/debug/bin")
    else()
        set(VCPKG_BIN_DIR "${VCPKG_ROOT_DIR}/installed/${VCPKG_TARGET_TRIPLET}/bin")
    endif()
    
    # Grab all the DLLs from the appropriate bin directory
    file(GLOB VCPKG_DLLS "${VCPKG_BIN_DIR}/*.dll")
    
    # Only try to copy if we actually found DLLs
    if(VCPKG_DLLS)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different 
                ${VCPKG_DLLS}
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
            COMMENT "Copying vcpkg ${CMAKE_BUILD_TYPE} dependency DLLs to output directory..."
        )
    endif()
endif()

# 2. Copy Compiler Runtime DLLs if we aren't statically linking (ASan builds)
if(ENABLE_ASAN)
    get_filename_component(COMPILER_BIN_DIR ${CMAKE_CXX_COMPILER} DIRECTORY)
    
    file(GLOB MINGW_RUNTIME_DLLS 
        "${COMPILER_BIN_DIR}/libasan-*.dll"
        "${COMPILER_BIN_DIR}/libgcc_s_*.dll"
        "${COMPILER_BIN_DIR}/libstdc++-*.dll"
        "${COMPILER_BIN_DIR}/libwinpthread-*.dll"
    )
    
    if(MINGW_RUNTIME_DLLS)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different 
                ${MINGW_RUNTIME_DLLS}
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
            COMMENT "Copying MinGW compiler runtime DLLs..."
        )
    else()
        message(WARNING "Could not find MinGW runtime DLLs in ${COMPILER_BIN_DIR}. You may need to copy them manually.")
    endif()
endif()