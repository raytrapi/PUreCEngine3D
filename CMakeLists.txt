cmake_minimum_required(VERSION 3.0.0)

project(2dMotorGame) 

find_program(conan conan)
execute_process(COMMAND ${conan} install -s build_type=${CMAKE_BUILD_TYPE} ${CMAKE_CURRENT_SOURCE_DIR})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup()
#find_package(libpng REQUIRED)

add_subdirectory("utilidades")
add_subdirectory("modules") 
add_subdirectory("components") 
add_subdirectory("lib")
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

add_subdirectory("graphics")


include_directories(
   src
   modules/src
   utilidades/librerias
	utilidades/log
   utilidades/files
   utilidades/timer
) 

file(GLOB CODIGO src/*.cpp utilidades/librerias/compile.cpp src/proyectos/*.cpp)# graphics/src/renderable/renderable.h
#file(GLOB MOTOR src/Motor/*/*.cpp src/Motor/*.cpp)

#file(GLOB MOTORGL src/terceros/*/*.cpp) 

if(WIN32)
	#file(GLOB CODIGOWIN src/windows/*/*.cpp src/windows/*.cpp)
	add_executable(2dMotorGame WIN32 ${CODIGO} )#${CODIGOWIN})

else()
	add_executable(2dMotorGame ${CODIGO})
endif()


set_property(TARGET 2dMotorGame PROPERTY CXX_STANDARD 20)

target_link_libraries( 2dMotorGame  motor_grafico utils components modules )


#add_subdirectory("ejemplos")

set(GUI_ONLY_BINARIES 2dMotorGame)

if (MSVC)
    # Tell MSVC to use main instead of WinMain for Windows subsystem executables
    set_target_properties(${GUI_ONLY_BINARIES} PROPERTIES
                         LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()

add_custom_command(
    TARGET 2dMotorGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_HOME_DIRECTORY}/src/proyectos/compiler
        ${CMAKE_BINARY_DIR}/bin/
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_HOME_DIRECTORY}/src/proyectos/defproj
        ${CMAKE_BINARY_DIR}/bin/
   )