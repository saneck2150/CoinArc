# Binance rest api
add_library(binance_rest
    binance/BinanceRestApi.cpp
)

target_include_directories(binance_rest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(binance_rest PUBLIC Qt6::Core Qt6::Network)

# Binance websocket api
add_library(binance_ws
    binance/BinanceWebSocketApi.cpp
)
target_include_directories(binance_ws PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(binance_ws PUBLIC Qt6::Core Qt6::Network Qt6::WebSockets)

# Linking
add_executable(CoinArc main.cpp)
target_link_libraries(CoinArc PRIVATE binance_rest binance_ws)