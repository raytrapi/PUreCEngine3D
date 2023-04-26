
include_directories(
   ../../utilidades/log
   ../../modules/physics
   ../../components/modulos
   ../../components/src/
   ../../vendors/JoltPhysics
)   

file(GLOB CODIGO src/*.cpp)
file(GLOB CODIGOJOLT src_jolt/*.cpp)
#add_library(physics_jolt_statica STATIC ${CODIGOJOLT} )
#set_property(TARGET physics_jolt_statica PROPERTY CXX_STANDARD 20)
#target_link_libraries( physics_jolt_statica Jolt)


if (("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows" OR "${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsStore") AND NOT MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20 /Zc:__cplusplus /Gm- /Wall /WX /MP /nologo /diagnostics:classic /FC /fp:except- /Zc:inline")
elseif ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux" OR "${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin" OR "${CMAKE_SYSTEM_NAME}" STREQUAL "iOS" OR MINGW OR EMSCRIPTEN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -I. -Wall -Werror")
endif()


add_library(physics_jolt SHARED ${CODIGOJOLT} )
set_property(TARGET physics_jolt PROPERTY CXX_STANDARD 20)
target_link_libraries( physics_jolt LINK_PUBLIC modules components  Jolt)
set_target_properties(physics_jolt PROPERTIES
	COMPILE_DEFINITIONS EXPORTAR_PHYSICS
    PUBLIC_HEADER src/joltphysics.h )


 if(WIN32)
	#target_link_libraries( mg_gl4 OpenGL32.lib Glu32.lib "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.lib")
    add_custom_command(
    TARGET physics_jolt POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/physics_jolt.dll
        ${CMAKE_BINARY_DIR}/bin/modulos
   )
elseif(UNIX)
	add_custom_command(
    TARGET physics_jolt POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/physics_jolt.so
        ${CMAKE_BINARY_DIR}/bin/modulos
    )
endif()