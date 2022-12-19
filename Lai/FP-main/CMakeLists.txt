cmake_minimum_required(VERSION 3.14)
project(FP_main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
include_directories(FP-main/Headers)

add_executable(FP_main
        FP-main/Headers/background.h
        FP-main/Headers/button.h
        FP-main/Headers/ConvertSketch.h
        FP-main/Headers/DrawMap.h
        FP-main/Headers/DrawText.h
        FP-main/Headers/Ghost.h
        FP-main/Headers/GhostManager.h
        FP-main/Headers/Global.h
        FP-main/Headers/MapCollision.h
        FP-main/Headers/Pacman.h
        FP-main/Headers/scoreBoard.h
        FP-main/ConvertSketch.cpp
        FP-main/DrawMap.cpp
        FP-main/DrawText.cpp
        FP-main/Ghost.cpp
        FP-main/GhostManager.cpp
        FP-main/main.cpp
        FP-main/MapCollision.cpp
        FP-main/Pacman.cpp)


find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(FP_main sfml-system sfml-window sfml-graphics sfml-audio sfml-network)