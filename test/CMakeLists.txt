cmake_minimum_required(VERSION 3.16)

set(This Tests)

set(Sources
        ImageAlignTest.cpp
        )
add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
        gtest_main
        ManipulationsLib
        )

add_test(
        Name ${This}
        COMMAND ${This}
)
