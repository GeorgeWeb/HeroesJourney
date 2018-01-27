cmake_minimum_required(VERSION 3.10)

project(Engine)

add_library(engine STATIC states/State.hpp states/StateMachine.hpp states/StateMachine.cpp)