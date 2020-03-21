cmake_minimum_required(VERSION 3.0.0)

project(2dMotorGame)
include_directories(
   src
) 
file(GLOB CODIGO src/*.cpp)
add_executable(2dMotorGame ${CODIGO} )