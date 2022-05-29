cmake_minimum_required(VERSION 3.17)
project(SnakeClient)

set(CMAKE_CXX_STANDARD 17)

add_executable(SnakeClient main.cpp Scene.cpp Scene.h Dollar.cpp Dollar.h Snake.cpp Snake.h HelpStructs.h HelpStructs.cpp Network.cpp Network.h)