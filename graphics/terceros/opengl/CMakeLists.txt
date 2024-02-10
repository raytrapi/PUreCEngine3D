
include_directories(
	../../src
   ../../modules/graphic
   ../../modules/src
) 
file(GLOB GRAFICO src/*.cpp src/*/*.cpp)
# terceros/*/*.cpp
add_library(motor_grafico_gl SHARED ${GRAFICO})
#set_target_properties( motor_grafico_gl
#    PROPERTIES
#    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/modulos"
#)
set_property(TARGET motor_grafico_gl PROPERTY CXX_STANDARD 23)
#target_link_libraries( motor_grafico_gl  ${CONAN_LIBS} )
target_link_libraries(motor_grafico_gl motor_grafico modules)

if(WIN32)
	target_link_libraries( motor_grafico_gl OpenGL32.lib Glu32.lib)
	add_custom_command(
    TARGET motor_grafico_gl POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/motor_grafico_gl.dll
        ${CMAKE_BINARY_DIR}/bin/modulos
   )
elseif(UNIX)
	add_custom_command(
    TARGET motor_grafico_gl POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/motor_grafico_gl.so
        ${CMAKE_BINARY_DIR}/bin/modulos
    )
endif()


