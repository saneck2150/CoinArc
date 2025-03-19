# CoinArc - Exchange Data Fetcher

A compact, cross-platform C++ project that retrieves and parses exchange market data via API.

## Features

- **Cross-Platform Build:** Uses CMake + Qt to support Windows, Linux, and macOS. (soon...)
- **HTTP Networking:** Perform robust HTTP/HTTPS requests.(soon...)
- **JSON Parsing:** Handling of JSON responses.(soon...)
- **Modular Architecture:** Designed for easy expansion (e.g., adding a GUI or additional API endpoints).(soon...)
- **Configurable API Integration:** Flexible integration with various exchange APIs for real-time or historical market data.(soon...)

## Installation

### Step 1 - Preinstalation

- **CMake** (version 3.14 or higher)
- **Git**
- **C++ Compiler** (supporting C++20)
- **Qt6**:

Ubuntu/Debian:
```bash
sudo apt update
sudo apt install qt6-base-dev qt6-base-dev-tools
```

### Step 2 - Build & Run

```bash
mkdir build
cd build
cmake ..
cmake --build .
./src/CoinArc
```

### For developers

REST API endpoint __/api/v3/klines__ from binance has this kind of structure:

[
  1499040000000,      // Open time

  "0.01634790",       // Open

  "0.80000000",       // High

  "0.01575800",       // Low

  "0.01577100",       // Close

  "148976.11427815",  // Volume

  1499644799999,      // Close time
  ... (other)
]