cmake_minimum_required(VERSION 3.17)
project(TPCGMIEI)

set(CMAKE_CXX_STANDARD 17)

add_executable(generator generator.cpp cone.cpp cone.h sphere.cpp sphere.h box.cpp box.h plane.cpp plane.h 
../utils/point_3d.cpp ../utils/point_3d.h ../utils/polar.cpp ../utils/polar.h )