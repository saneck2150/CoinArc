add_library(binance_rest
    ${CMAKE_CURRENT_SOURCE_DIR}/binance/BinanceRestApi.cpp
)
target_include_directories(binance_rest PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/binance
)
target_link_libraries(binance_rest PUBLIC
    Qt6::Core
    Qt6::Network
)

add_library(binance_ws
    ${CMAKE_CURRENT_SOURCE_DIR}/binance/BinanceWebSocketApi.cpp
)
target_include_directories(binance_ws PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/binance
)
target_link_libraries(binance_ws PUBLIC
    Qt6::Core
    Qt6::Network
    Qt6::WebSockets
)

add_executable(CoinArc
    main.cpp
    binance/BinanceRestApi.cpp
    binance/BinanceWebSocketApi.cpp
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