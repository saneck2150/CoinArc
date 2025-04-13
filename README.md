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
./CoinArc
```

### How to use it Console
```bash
./CoinArc

#Change ticker symbol("BTCUSDT, ETHUSDT...")
-s or --symbol "ticker symbol" 

#Change Interval ("1m,15m,1h"):
-i or --interval "interval"

#Example:
./ConsoleKlineApp -s ETHUSDT -i 15m
```

### For developers

REST API endpoint __/api/v3/klines__ from binance has this kind of structure:

```cpp
[
{
  "e": "kline",
  "E": 123456789,      // Event time
  "s": "BTCUSDT",      // Symbol
  "k": {
    "t": 123400000,    // Kline start time
    "T": 123460000,    // Kline close time
    "s": "BTCUSDT",    // Symbol
    "i": "1m",         // Interval
    "f": 100,          // First trade ID
    "L": 200,          // Last trade ID
    "o": "0.0010",     // Open
    "c": "0.0020",     // Close
    "h": "0.0025",     // High
    "l": "0.0015",     // Low
    "v": "1000",       // Base asset volume
    "n": 100,          // Number of trades
    "x": false,        // Is this kline closed?
    ...
  }
}

]
```