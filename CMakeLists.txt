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
        scripts/Camera.h
        scripts/player.h
        scripts/Hornet.h
        scripts/Knight.cpp
        scripts/Knight.h
        scripts/resourses.cpp
        scripts/Scene.cpp
        scripts/Scene.h
        scripts/Gamescene.cpp
        scripts/Gamescene.h
        scripts/SceneManager.cpp
        scripts/SceneManager.h
        scripts/Menuscene.cpp
        scripts/Menuscene.h
        scripts/collision_layer.h
        scripts/collision_box.h
        scripts/collision_manager.h
        scripts/collision_manager.cpp
        scripts/player.cpp
        scripts/sword.cpp
        scripts/sword.h
        scripts/barb.cpp
        scripts/barb.h
        scripts/enemy.cpp
        scripts/enemy.h)

target_link_libraries(Hollowknight_demo msimg32)

