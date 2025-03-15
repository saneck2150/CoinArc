#Flags
cmake_minimum_required(VERSION 3.14)
project(CoinArc VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Import
include(FetchContent)

FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2 
)
FetchContent_MakeAvailable(nlohmann_json)

FetchContent_Declare(
  cpp_httplib
  GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
  GIT_TAG v0.10.8
)
FetchContent_MakeAvailable(cpp_httplib)

#Linking
add_executable(CoinArc src/main.cpp)
target_link_libraries(CoinArc PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(CoinArc PRIVATE ${cpp_httplib_SOURCE_DIR})

#Test ....