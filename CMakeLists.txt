# Flags
cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 20)

# Import
project(CoinArc)

include(ExternalProject)
ExternalProject_Add(
    Boost
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG master
    PREFIX ${CMAKE_SOURCE_DIR}/third_party/boost
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)

# Linking
add_executable(CoinArc src/main.cpp)

add_dependencies(CoinArc Boost)

target_include_directories(CoinArc PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/third_party/boost/src/Boost
    )

# Test
#...