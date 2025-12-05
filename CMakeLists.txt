cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME compiler)
project(${PROJECT_NAME})

# 设置 C++ 标准（根据需要选择，如 C++17/C++20）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # 禁用 GNU 扩展

# 设置编译器为 clang++
set(CMAKE_CXX_COMPILER clang++)

# 导出编译命令
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cpp)