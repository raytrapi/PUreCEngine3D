cmake_minimum_required(VERSION 3.0.0)

project(2dMotorGame)
find_program(conan conan)
execute_process(COMMAND ${conan} install -s build_type=${CMAKE_BUILD_TYPE} ${CMAKE_CURRENT_SOURCE_DIR})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup()

add_subdirectory("Motor gráfico")
add_subdirectory("utilidades")

include_directories(
   src
   utilidades/librerias
	utilidades/log
) 

file(GLOB CODIGO src/*.cpp )
#file(GLOB MOTOR src/Motor/*/*.cpp src/Motor/*.cpp)

#file(GLOB MOTORGL src/terceros/*/*.cpp)

if(WIN32)
	file(GLOB CODIGOWIN src/windows/*/*.cpp src/windows/*.cpp)
	add_executable(2dMotorGame WIN32 ${CODIGO} ${CODIGOWIN})
else()
	add_executable(2dMotorGame ${CODIGO})
endif()


target_link_libraries( 2dMotorGame  motor_grafico utilidades)

