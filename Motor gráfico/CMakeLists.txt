
include_directories(
   ../utilidades/log
) 

file(GLOB GRAFICO src/*.cpp src/*/*.cpp terceros/imagenes/*.cpp)
# terceros/*/*.cpp
add_library(motor_grafico SHARED ${GRAFICO})
target_link_libraries( motor_grafico  ${CONAN_LIBS} utilidades)



#if(WIN32)
	#target_link_libraries( motor_grafico OpenGL32.lib Glu32.lib)
#elseif(UNIX)
	 
#endif()
add_subdirectory("terceros/opengl")
set_target_properties(motor_grafico PROPERTIES
	COMPILE_DEFINITIONS EXPORTAR_MODULO_GRAFICO
    PUBLIC_HEADER src/motor.h )