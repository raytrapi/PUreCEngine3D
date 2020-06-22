
include_directories(
   ../utilidades/log
	../src
   src
) 


file(GLOB GRAFICO src/motor.cpp terceros/imagenes/*.cpp)
file(GLOB RENDERIZABLES src/renderable/object.cpp src/renderable/pixel.cpp src/renderable/img.cpp src/renderable/renderable.cpp src/renderable/cube.cpp )
# terceros/*/*.cpp
add_library(motor_grafico SHARED  ${RENDERIZABLES} ${GRAFICO})
target_link_libraries( motor_grafico  ${CONAN_LIBS} utilidades modulos)
set_target_properties(motor_grafico PROPERTIES
	COMPILE_DEFINITIONS EXPORTAR_MODULO_GRAFICO
    PUBLIC_HEADER src/motor.h )



#if(WIN32)
	#target_link_libraries( motor_grafico OpenGL32.lib Glu32.lib)
#elseif(UNIX)
	 
#endif()

#[[if(WIN32)
	add_custom_command(
    TARGET motor_grafico POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/motor_grafico.dll
        ${CMAKE_BINARY_DIR}/bin/modulos
   )
elseif(UNIX)
	add_custom_command(
    TARGET motor_grafico POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/motor_grafico.so
        ${CMAKE_BINARY_DIR}/bin/modulos
    )
endif()]]

add_subdirectory("terceros/opengl")
