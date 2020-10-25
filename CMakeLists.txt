cmake_minimum_required(VERSION 3.17)

set (This Example)

project(${This} CXX)

find_package(OpenCV REQUIRED)
MESSAGE(STATUS "Include dirs ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "LINK LIBRARIES ${OpenCV_LIBS}")
include_directories(${OpenCV_INCLUDE_DIRS})

enable_testing()

add_subdirectory(libs/googletest)

set(Sources
        src/Example.cpp
        )
set(Headers
        src/Example.hpp
        )

add_library(${This}Lib STATIC ${Sources} ${Headers})

add_executable(${This} main.cpp)

target_link_libraries(${This} ${This}Lib)
target_link_libraries(${This} ${OpenCV_LIBS})

add_subdirectory(test)