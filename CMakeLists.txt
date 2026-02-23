cmake_minimum_required(VERSION 3.31)
project(breakout)

add_subdirectory(caffeine-gl)

add_executable(breakout
        src/main.cpp
        src/game/BreakoutGame.cpp
        include/game/BreakoutGame.h
)

target_compile_features(breakout PRIVATE cxx_std_17)

target_include_directories(breakout PRIVATE
        include
)

target_link_libraries(breakout PRIVATE
        caffeine_gl
)

add_custom_target(copy_resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        ${CMAKE_BINARY_DIR}/resources
)

add_dependencies(breakout copy_resources)

target_compile_definitions(breakout PRIVATE
        RESOURCE_PATH="${CMAKE_BINARY_DIR}/resources/"
)