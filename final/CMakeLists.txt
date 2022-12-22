cmake_minimum_required(VERSION 3.23)
project(WithNew)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

include_directories(Main)
include_directories(Resources)

add_executable(WithNew
        Main/Headers/Background.hpp
        Main/Headers/Button.h
        Main/Headers/ConvertSketch.h
        Main/Headers/DrawMap.h
        Main/Headers/Ghost.h
        Main/Headers/GhostManager.h
        Main/Headers/Global.h
        Main/Headers/MapCollision.h
        Main/Headers/Pacman.h
        Main/Headers/ScoreBoard.hpp
        Main/ConvertSketch.cpp
        Main/DrawMap.cpp
        Main/Ghost.cpp
        Main/GhostManager.cpp
        Main/main.cpp
        Main/MapCollision.cpp
        Main/Pacman.cpp Main/Headers/Button.cpp)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(WithNew sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

