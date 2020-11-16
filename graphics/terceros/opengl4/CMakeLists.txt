
set(GLFW_SOURCE_DIR "../../../../glfw")
include_directories(
	../../src
   ../../modules/src
   ../../../components/src
   ../../../components/modulos/cameras
   ../../../components/modulos/renderables
   ../../modules/graphic
   ../../modules/tape
   "${GLFW_SOURCE_DIR}/deps"
   "${GLFW_SOURCE_DIR}/include"

) 
set(GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h"
            "${GLFW_SOURCE_DIR}/deps/glad_gl.c")
             
file(GLOB GRAFICO src/*.cpp src/*/*.cpp)
add_library(mg_gl4 SHARED ${GRAFICO} ${GLAD_GL})

set_property(TARGET mg_gl4 PROPERTY CXX_STANDARD 20)
target_link_libraries(mg_gl4 motor_grafico modules components)

if(WIN32)
	target_link_libraries( mg_gl4 OpenGL32.lib Glu32.lib "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.lib")
	add_custom_command(
    TARGET mg_gl4 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/mg_gl4.dll
        ${CMAKE_BINARY_DIR}/bin/modulos
   )
elseif(UNIX)
	add_custom_command(
    TARGET mg_gl4 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/mg_gl4.so
        ${CMAKE_BINARY_DIR}/bin/modulos
    )
endif()

make_directory(${CMAKE_BINARY_DIR}/bin/shaders)
file(GLOB SHADERS shaders/*/*.glsl)
add_custom_command(
    TARGET mg_gl4 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SHADERS}
        ${CMAKE_BINARY_DIR}/bin/shaders
   )
