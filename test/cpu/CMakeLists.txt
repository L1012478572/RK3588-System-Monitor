cmake_minimum_required(VERSION 3.10)
project(cpu_test)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 获取当前 CMakeLists.txt 所在的绝对路径
get_filename_component(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR} ABSOLUTE)
# 打印 TEST_DIR
message(STATUS "TEST_DIR: ${TEST_DIR}")
# 获取项目根目录路径
get_filename_component(PROJECT_ROOT ${TEST_DIR}/../.. ABSOLUTE)
# 打印 PROJECT_ROOT
message(STATUS "PROJECT_ROOT: ${PROJECT_ROOT}")

# 添加头文件路径
include_directories(
    ${PROJECT_ROOT}/src
)

# 添加源文件
set(SOURCES
    main.cpp
    ${PROJECT_ROOT}/src/CPUUsage.cpp
)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})
# 打印 SOURCES
message(STATUS "SOURCES: ${SOURCES}")

# # 设置目标文件路径
# set_target_properties(${PROJECT_NAME} PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT}/bin
# )   