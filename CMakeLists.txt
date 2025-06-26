cmake_minimum_required(VERSION 3.20)

project(wzy_stl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# 添加库目标
file(GLOB_RECURSE WZY_STL_SRC src/*.cpp src/*.hpp src/*.cxx)
add_library(wzy_stl ${WZY_STL_SRC})
target_include_directories(wzy_stl PUBLIC src)

# 设置可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 遍历 test 目录下所有 .cpp 文件，分别生成可执行文件
file(GLOB TEST_SOURCES test/*.cpp)
foreach(test_src ${TEST_SOURCES})
    # 获取文件名（不带路径和扩展名）
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
    target_link_libraries(${test_name} PRIVATE wzy_stl)
    target_include_directories(${test_name} PRIVATE src)
    set_target_properties(${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
endforeach()