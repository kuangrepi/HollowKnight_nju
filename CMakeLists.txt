cmake_minimum_required(VERSION 3.28)
project(Hollowknight_demo)

set(CMAKE_CXX_STANDARD 11)

link_libraries(libeasyx.a)
add_executable(Hollowknight_demo scripts/main.cpp
        scripts/define.h
        scripts/Timer.cpp
        scripts/Timer.h
        scripts/Atlas.cpp
        scripts/Atlas.h
        scripts/Animation.cpp
        scripts/Animation.h
        scripts/util.h
        scripts/Vector2.cpp
        scripts/Vector2.h
        scripts/Camera.cpp
        scripts/Camera.h)

target_link_libraries(Hollowknight_demo msimg32)

