# Exchange Data Fetcher

A compact, cross-platform C++ project for fetching and processing API data.

## Overview

CoinArc serves as a starting point for creating a lightweight application that retrieves data from an API, processes the JSON response, and performs basic analysis.

## Features

- **Cross-Platform Build**: Uses CMake to enable building on Windows, Linux, and macOS. (SOON...)
- **HTTP Client**: Utilizes [cpp-httplib](https://github.com/yhirose/cpp-httplib), a header-only, easy-to-use HTTP library. (SOON...)
- **JSON Parsing**: Employs [nlohmann/json](https://github.com/nlohmann/json) for intuitive and efficient JSON handling. (SOON...)
- **Automated Dependency Management**: Integrates FetchContent in CMake to automatically download and configure external libraries. (SOON...)
- If the project will expand, we will switch to Boost lib.

## Dependencies

- **CMake (>= 3.14)**
- **cpp-httplib** (fetched automatically via CMake's FetchContent)
- **nlohmann/json** (fetched automatically via CMake's FetchContent)

## Getting Started
### Cloning the Repository

```bash
   git clone https://github.com/saneck2150/CoinArc.git
   cd CoinArc
   mkdir build
   cd build
   cmake ..
   cmake --build .

   ./my_project - for Lunix/MacOS
   my_project.exe - for Windows

