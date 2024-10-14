cmake_minimum_required(VERSION 3.5.0)
project(Poker VERSION 0.1.0 LANGUAGES C CXX)

add_executable(Poker src/main.cpp src/utilities.cpp src/globals.cpp src/classes/game.cpp src/classes/players.cpp)