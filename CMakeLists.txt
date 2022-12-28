cmake_minimum_required(VERSION 3.24)
project(autobrake)

set(CMAKE_CXX_STANDARD 17)

add_executable(autobrake main.cpp AutoBrake.cpp AutoBrake.h Events.cpp Events.h Assert.h Harness.h)
