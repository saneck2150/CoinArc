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

# CMake Modules
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/BinanceCore.cmake)

#CoinArc
add_executable(CoinArc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/binance/BinanceRestApi.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/binance/BinanceWebSocketApi.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/binance/BinanceRunner.cpp
)

target_link_libraries(CoinArc PRIVATE
    Qt6::Core
    Qt6::Network
    Qt6::WebSockets
    Qt6::Widgets
    Qt6::Charts
    binance_rest
    binance_ws
)
target_include_directories(CoinArc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


# Tests...