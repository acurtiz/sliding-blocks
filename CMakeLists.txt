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

# Link to SlidingBlocksNetworking library
find_path(SLIDING_BLOCKS_NETWORKING_INCLUDE_DIR
        NAMES "message/network_message.h"
        HINTS "/Users/alex/CLionProjects/SlidingBlocksNetworking/include"
        REQUIRED)
include_directories(${SLIDING_BLOCKS_NETWORKING_INCLUDE_DIR})
find_library(SLIDING_BLOCKS_NETWORKING_LIBRARY
        NAMES SlidingBlocksNetworking
        HINTS /Users/alex/CLionProjects/SlidingBlocksNetworking/build)
target_link_libraries(SlidingBlocks LINK_PUBLIC ${SLIDING_BLOCKS_NETWORKING_LIBRARY})

# Link to SDL2 library
find_library(SDL2_LIBRARY
        NAMES SDL2
        HINTS /Library/Frameworks)
target_link_libraries(SlidingBlocks LINK_PUBLIC ${SDL2_LIBRARY})

# Link to SDL2_ttf library
find_library(SDL2_TTF_LIBRARY
        NAMES SDL2_ttf
        HINTS /Library/Frameworks)
target_link_libraries(SlidingBlocks LINK_PUBLIC ${SDL2_TTF_LIBRARY})

# Link to Enet
find_library(ENET_LIBRARY
        Names ENet
        HINTS /usr/local/lib)
find_path(ENET_INCLUDE_DIR
        enet/enet.h)
include_directories(${ENET_INCLUDE_DIR})
target_link_libraries(SlidingBlocks LINK_PUBLIC ${ENET_LIBRARY})

# Include Boost
set(BOOST_HEADER_DIRECTORY /Users/alex/Libraries/boost_1_76_0)
include_directories(${BOOST_HEADER_DIRECTORY})
