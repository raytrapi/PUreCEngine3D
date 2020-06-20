cmake_minimum_required(VERSION 3.0.0)

project(2dMotorGame)

find_program(conan conan)
execute_process(COMMAND ${conan} install -s build_type=${CMAKE_BUILD_TYPE} ${CMAKE_CURRENT_SOURCE_DIR})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup()


add_library(modulos SHARED src/modulos.cpp)
set_target_properties(modulos PROPERTIES
	COMPILE_DEFINITIONS EXPORTAR_MODULO
    PUBLIC_HEADER src/modulos.h )

make_directory(${CMAKE_BINARY_DIR}/bin/modulos)
#[[if(WIN32)
	add_custom_command(
    TARGET modulos POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/modulos.dll
        ${CMAKE_BINARY_DIR}/bin/modulos
   )
elseif(UNIX)
	add_custom_command(
    TARGET modulos POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/modulos.so
        ${CMAKE_BINARY_DIR}/bin/modulos
    )
endif()]]
add_subdirectory("utilidades")
add_subdirectory("graphics")
add_subdirectory("cartucho")

include_directories(
   src
   utilidades/librerias
	utilidades/log
) 

file(GLOB CODIGO src/*.cpp )# graphics/src/renderable/renderable.h
#file(GLOB MOTOR src/Motor/*/*.cpp src/Motor/*.cpp)

#file(GLOB MOTORGL src/terceros/*/*.cpp)

if(WIN32)
	file(GLOB CODIGOWIN src/windows/*/*.cpp src/windows/*.cpp)
	add_executable(2dMotorGame WIN32 ${CODIGO} ${CODIGOWIN})
else()
	add_executable(2dMotorGame ${CODIGO})
endif()
set_property(TARGET 2dMotorGame PROPERTY CXX_STANDARD 20)

target_link_libraries( 2dMotorGame  motor_grafico utilidades cartucho)


add_subdirectory("ejemplos")
