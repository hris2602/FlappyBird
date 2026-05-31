cmake_minimum_required(VERSION 3.15)
project(FlappyBird C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# vcpkg makes these work flawlessly
find_package(Freetype REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED) # Since you installed sdl2 via vcpkg as well

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/glad.c 
    src/Application.cpp
    src/stb_image.cpp
    src/Shader.cpp
)

target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++ -static)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Freetype::Freetype
    glm::glm
    SDL2::SDL2main
    SDL2::SDL2      # <-- This is the core library you were missing!
    opengl32
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> 
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND_EXPAND_LISTS
)