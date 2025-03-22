# Flags
cmake_minimum_required(VERSION 3.15)
project(CoinArc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Pkg Find
find_package(Qt6 6.2 COMPONENTS 
    Core 
    Network 
    WebSockets 
    Widgets
    Charts
    REQUIRED
)

# Subdirectories
add_subdirectory(src)

# Tests...