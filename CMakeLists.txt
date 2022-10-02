cmake_minimum_required(VERSION 3.16)

project(lfu)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCES main.cpp)

add_executable (${PROJECT_NAME} ${SOURCES})



#add_compile_options (-g -Werror -Wall -Wextra -Wpedantic)

target_include_directories (${PROJECT_NAME} PRIVATE lfu/include idealalg/include)


enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set (TEST_SOURCES test_generate/unit_tests.cpp)

add_executable(unit_tests ${TEST_SOURCES})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
set(CMAKE_CXX_CLANG_TIDY 
    "clang-tidy;
    -header-filter=.;
    -checks=*;
    -warnings-as-errors=*")

target_include_directories (unit_tests PRIVATE lfu/include idealalg/include)
target_link_libraries(unit_tests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)