#REST API
add_library(binance_rest
    ${CMAKE_CURRENT_SOURCE_DIR}/src/binance/BinanceRestApi.cpp
)
target_include_directories(binance_rest PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/binance
)
target_link_libraries(binance_rest PUBLIC
    Qt6::Core
    Qt6::Network
)

#Websocket API
add_library(binance_ws
    ${CMAKE_CURRENT_SOURCE_DIR}/src/binance/BinanceWebSocketApi.cpp
)
target_include_directories(binance_ws PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/binance
)
target_link_libraries(binance_ws PUBLIC
    Qt6::Core
    Qt6::Network
    Qt6::WebSockets
)

#Binance API Runner
add_library(binance_run
    ${CMAKE_CURRENT_SOURCE_DIR}/src/binance/BinanceRunner.cpp
)
target_include_directories(binance_run PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/binance
)
target_link_libraries(binance_run PUBLIC
    Qt6::Core
    Qt6::Network
    Qt6::WebSockets
    binance_rest
    binance_ws
)