cmake_minimum_required(VERSION 3.16)

project(lfu)

#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCES main.cpp)

#set( CMAKE_VERBOSE_MAKEFILE on )
#set (HEADERS
#    idealalg/include/ideal.h
#    lfu/include/lfu.h)

add_executable (${PROJECT_NAME} ${SOURCES})



#add_compile_options (-g -Werror -Wall -Wextra -Wpedantic)

#target_include_directories (${PROJECT_NAME} PRIVATE lfu/include idealalg/include)

#cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

#project(LFU VERSION 0.3 LANGUAGES CXX)

#add_executable(LFU main.cpp)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")