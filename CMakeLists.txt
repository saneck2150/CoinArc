# Flags
cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 20)

message(STATUS "Building ${PROJECT_NAME}")
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
message(STATUS "Be patient, Boost moduls installation may take a while...")

# Import
project(CoinArc)
include(ExternalProject)

# Add boost.beast
ExternalProject_Add(
    BoostBeast
    GIT_REPOSITORY https://github.com/boostorg/beast.git
    GIT_TAG master
    PREFIX ${CMAKE_SOURCE_DIR}/third_party/boost/beast
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)

# Add boost.json
ExternalProject_Add(
    BoostJson
    GIT_REPOSITORY https://github.com/boostorg/json.git
    GIT_TAG master
    PREFIX ${CMAKE_SOURCE_DIR}/third_party/boost/json
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)

message(STATUS "Boost modules installed")

# Linking
add_executable(CoinArc src/main.cpp)

add_dependencies(CoinArc 
    BoostBeast
    BoostJson
)

target_include_directories(CoinArc PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/third_party/boost/beast/src/BoostBeast/include
    ${CMAKE_SOURCE_DIR}/third_party/boost/json/src/BoostJson/include
)

message(STATUS "Boost modules linked")

# Test
#...