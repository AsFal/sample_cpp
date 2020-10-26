cmake_minimum_required(VERSION 3.16)

set(This ExampleTest)

set(Sources
        ExampleTest.cpp
        )
add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
        gtest_main
        ExampleLib
        )

add_test(
        Name ${This}
        COMMAND ${This}
)
