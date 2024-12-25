cmake_minimum_required(VERSION 3.19)
project(SlidingBlocks)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Target for generating executable
include_directories(include)
include_directories(external/include)
file(GLOB_RECURSE SOURCES "src/*.cc")
message("Sources are: ${SOURCES}")
add_executable(SlidingBlocks ${SOURCES} assets/)

# Target for copying assets into build directory.
# By using custom target, we can ensure modifications get copied as well.
add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
        )
add_dependencies(SlidingBlocks copy_assets)

# SDL2: Link to libraries & include necessary headers.
find_package(SDL2 REQUIRED)
find_package(SDL2_TTF REQUIRED)
target_link_libraries(SlidingBlocks PUBLIC SDL2::SDL2 SDL2_ttf::SDL2_ttf)

# Boost: Include necessary headers.
find_package(Boost REQUIRED COMPONENTS format)
include_directories(${Boost_INCLUDE_DIRS})
