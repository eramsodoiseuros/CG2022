cmake_minimum_required(VERSION 3.17)
project(TPCGMIEI)

set(CMAKE_CXX_STANDARD 17)

add_executable(generator src/generator.cpp src/cone.cpp headers/cone.h src/sphere.cpp headers/sphere.h src/box.cpp headers/box.h src/plane.cpp headers/plane.h 
../utils/point_3d.cpp ../utils/point_3d.h ../utils/polar.cpp ../utils/polar.h src/patch.cpp headers/patch.h)