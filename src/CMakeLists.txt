add_library(binance_rest
    binance/BinanceRestApi.cpp
)

# Linking
target_include_directories(binance_rest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(binance_rest PUBLIC Qt6::Core Qt6::Network)
add_executable(CoinArc main.cpp)
target_link_libraries(CoinArc PRIVATE binance_rest)