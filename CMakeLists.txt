cmake_minimum_required(VERSION 3.16)

set (This Manipulations)

project(${This} CXX)

find_package(OpenCV REQUIRED)
MESSAGE(STATUS "Include dirs ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "LINK LIBRARIES ${OpenCV_LIBS}")
include_directories(${OpenCV_INCLUDE_DIRS})

enable_testing()

add_subdirectory(libs/googletest)

set(Sources
        src/ROIReader.cpp
        src/ImageAlign.cpp
        )
set(Headers
        src/ImageReader.hpp
        src/ROIReader.hpp
        src/ImageAlign.hpp
        )

add_library(${This}Lib STATIC ${Sources} ${Headers})

add_executable(${This} main.cpp)

target_link_libraries(${This} ${This}Lib)
target_link_libraries(${This}Lib ${OpenCV_LIBS})

add_subdirectory(test)