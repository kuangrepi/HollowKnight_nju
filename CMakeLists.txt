cmake_minimum_required(VERSION 3.28)
project(Hollowknight_demo)

set(CMAKE_CXX_STANDARD 11)

link_libraries(libeasyx.a)
add_executable(Hollowknight_demo scripts/main.cpp
        scripts/define.h
        scripts/Timer.cpp
        scripts/Timer.h)
