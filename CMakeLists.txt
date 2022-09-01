cmake_minimum_required(VERSION 3.23)
project(xpwebm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/include/SFML -lsfml-graphics -lsfml-window -lsfml-system")

add_executable(xpwebm main.cpp Game.cpp Game.h enemy.h)
