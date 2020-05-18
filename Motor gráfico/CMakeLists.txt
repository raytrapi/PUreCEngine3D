

file(GLOB GRAFICO src/*.cpp src/*/*.cpp terceros/imagenes/*.cpp)
# terceros/*/*.cpp
add_library(motor_grafico SHARED ${GRAFICO})

target_link_libraries( motor_grafico  ${CONAN_LIBS})
#if(WIN32)
	#target_link_libraries( motor_grafico OpenGL32.lib Glu32.lib)
#elseif(UNIX)
	
#endif()
add_subdirectory("terceros/opengl")