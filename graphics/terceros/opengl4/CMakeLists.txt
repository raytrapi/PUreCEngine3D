
#set(GLFW_SOURCE_DIR "../../../../glfw")
set(GLAD_DIR "../../../vendors/glad")
include_directories(
	../../src
   ../../modules/src
   ../../../components/src
   ../../../components/modulos/cameras
   ../../../components/modulos/renderables
   ../../modules/graphic
   ../../modules/tape
   ../../../vendors/imgui-node-editor
   ../
   #"${GLFW_SOURCE_DIR}/deps" 
   #"${GLFW_SOURCE_DIR}/include" 
   "${GLAD_DIR}/include" 
) 
set(GLAD_GL #"${GLAD_DIR}/include/glad/gl.h"
            "${GLAD_DIR}/src/gl.c"  
			  
)  

             
file(GLOB GRAFICO src/*.cpp src/*/*.cpp src/*/*/*.cpp)
add_library(mg_gl4 SHARED ${GRAFICO} ${GLAD_GL} ) 
#add_library(mg_gl4 SHARED ${GRAFICO} ) 
  
set_property(TARGET mg_gl4 PROPERTY CXX_STANDARD 23)
target_link_libraries(mg_gl4 utils globals imports motor_grafico modules components glfw3 pc_interface    )
 
    
if(WIN32)
	#target_link_libraries( mg_gl4 OpenGL32.lib Glu32.lib "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.lib")
    target_link_libraries( mg_gl4 OpenGL32.lib Glu32.lib ${CONAN_LIBS} )
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

#make_directory(${CMAKE_BINARY_DIR}/bin/shaders)
#file(GLOB SHADERS shaders/*/*.glsl)
#add_custom_command(
#    TARGET mg_gl4 POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        ${SHADERS}
#        ${CMAKE_BINARY_DIR}/bin/shaders
#   )
add_custom_command(
    TARGET mg_gl4 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
        ${CMAKE_HOME_DIRECTORY}/graphics/terceros/opengl4/shaders/GLSL
        ${CMAKE_BINARY_DIR}/bin/shaders
)
add_custom_command(
    TARGET mg_gl4 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
        ${CMAKE_HOME_DIRECTORY}/resources
        ${CMAKE_BINARY_DIR}/bin/resources
)  
#add_custom_command(
#    TARGET mg_gl4 POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
#        "${CMAKE_HOME_DIRECTORY}/graphics/terceros/opengl4/src/imgui/imgui.ini"
#        ${CMAKE_BINARY_DIR}/bin
#)