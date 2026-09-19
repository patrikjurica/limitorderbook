# 1. Minimum version requirement for CMake
cmake_minimum_required(VERSION 3.15)

# 2. Project name, version, and language
project(limit_order_book VERSION 1.0 LANGUAGES CXX)

# 3. Set the C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. Define the executable and the source files it needs
add_executable(lob
        src/main.cpp
        src/order_types.cpp.cpp
)