cmake_minimum_required(VERSION 3.31)
project(breakout)

set(CMAKE_CXX_STANDARD 17)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)

include_directories(include)

add_executable(breakout
        src/main.cpp
        src/glad.c
        src/game/Game.cpp
        src/game/Game.h
        src/gfx/Shader.cpp
        src/gfx/Shader.h
        src/gfx/Texture.cpp
        src/gfx/Texture.h
        src/gfx/ResourceManager.cpp
        src/gfx/ResourceManager.h
        src/gfx/stb.cpp
        src/gfx/stb_image.h
        src/gfx/SpriteRenderer.cpp
        src/gfx/SpriteRenderer.h
        src/game/GameLevel.cpp
        src/game/GameLevel.h
        src/game/GameObject.cpp
        src/game/GameObject.h
)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # For Windows cross-compiling with MinGW-w64
    target_link_libraries(${PROJECT_NAME} PRIVATE
            ${CMAKE_SOURCE_DIR}/lib/windows/libglfw3.a
            opengl32  # Windows OpenGL library
    )
else()
    # Native Linux build
    target_link_libraries(${PROJECT_NAME} PRIVATE
            z
            minizip
            ${CMAKE_SOURCE_DIR}/lib/linux/libglfw3.a
            #${CMAKE_SOURCE_DIR}/lib/linux/libassimp.a
            OpenGL::GL  # Linux OpenGL target from find_package
            dl
            pthread
            wayland-client
            wayland-cursor
            wayland-egl
            xkbcommon
    )
endif()