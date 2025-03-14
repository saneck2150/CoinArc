# Exchange Data Fetcher

A compact, cross-platform C++ project that retrieves and parses exchange market data via API. The application currently 
demonstrates a console-based implementation using Boost.Beast for HTTP networking and Boost.JSON for JSON parsing, with plans for future expansion into graphical user interfaces.

## Features

- **Cross-Platform Build:** Uses CMake to support Windows, Linux, and macOS. (soon...)
- **HTTP Networking:** Leverages Boost.Beast to perform robust HTTP/HTTPS requests.(soon...)
- **JSON Parsing:** Utilizes Boost.JSON for efficient handling of JSON responses.(soon...)
- **Modular Architecture:** Designed for easy expansion (e.g., adding a GUI or additional API endpoints).(soon...)
- **Configurable API Integration:** Flexible integration with various exchange APIs for real-time or historical market data.(soon...)

## Installation

### Prerequisites

- **CMake** (version 3.14 or higher)
- **Git**
- **C++ Compiler** (supporting C++20)

### Steps

1. **Clone the repository:**
   ```bash
   git clone https://github.com/saneck2150/CoinArc.git
   cd CoinArc
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ./CoinArc