cmake_minimum_required(VERSION 3.10)
project(CompressPatch)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 1)

include_directories(include)
# 添加可执行文件

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/PatchCompressor.cpp
        src/VariableLengthEncoder.cpp
        src/VariableLengthEncoder.cpp
)

add_executable(Test
        src/PatchCompressor.cpp
        src/VariableLengthEncoder.cpp
        test/main.cpp
)
# 包含头文件目录（如果头文件不在当前目录下，需要指定路径）
include_directories(${CMAKE_SOURCE_DIR})
