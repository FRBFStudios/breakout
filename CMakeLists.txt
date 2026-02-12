cmake_minimum_required(VERSION 3.31)
project(breakout)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(caffeine-gl)

add_executable(breakout
        src/main.cpp
        src/game/BreakoutGame.cpp
        include/game/BreakoutGame.h
)

target_include_directories(breakout PRIVATE include)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # For Windows cross-compiling with MinGW-w64
    target_link_libraries(${PROJECT_NAME} PRIVATE
            caffeine_gl
    )
    target_link_options(breakout PRIVATE
            -static
            -static-libgcc
            -static-libstdc++
    )
else()
    # Native Linux build
    target_link_libraries(${PROJECT_NAME} PRIVATE
            caffeine_gl
    )
endif()

file(GLOB_RECURSE GAME_RESOURCES "${CMAKE_SOURCE_DIR}/resources/*")

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        ${CMAKE_BINARY_DIR}/resources
)

add_dependencies(breakout copy_resources)

target_compile_definitions(breakout PRIVATE
        RESOURCE_PATH="${CMAKE_BINARY_DIR}/resources/"
)