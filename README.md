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
```bash Ubuntu/Debian
sudo apt update
sudo apt install qt6-base-dev qt6-base-dev-tools
```
```bash Arch Linux
sudo pacman -S qt6-base qt6-network
```
```bash Fedora
sudo dnf install qt6-qtbase-devel qt6-qtnetwork-devel
```

### Step 2 - Build & Run

```bash
mkdir build
cd build
cmake ..
cmake --build .
./src/CoinArc
```