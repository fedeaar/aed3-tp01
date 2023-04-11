cmake_minimum_required(VERSION 3.16)
project(potencia)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")

# add_library(gtest STATIC tests/gtest-1.8.1/gtest-all.cc)
# add_library(gtest_main STATIC tests/gtest-1.8.1/gtest_main.cc)

# set(SOURCE_FILES src/ej2.h src/ej2.cpp)
        
# add_executable(TESTS-ej2 ${SOURCE_FILES} tests/ej2-tests.cpp)
# target_link_libraries(TESTS-ej2 gtest gtest_main)

add_executable(ej2 main.cpp)
