#CMake flags 
cmake_minimum_required(VERSION 3.15)
project(CoinArc LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Qt import
find_package(Qt6 6.2 COMPONENTS Core Network WebSockets REQUIRED)

# Subdirectories
add_subdirectory(src)