cmake_minimum_required(VERSION 3.24)
project(autobreak)

set(CMAKE_CXX_STANDARD 17)

add_executable(autobreak main.cpp AutoBreak.cpp AutoBreak.h Events.cpp Events.h Assert.h Harness.h)
