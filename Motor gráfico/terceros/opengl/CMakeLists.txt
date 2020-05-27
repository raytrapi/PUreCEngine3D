
include_directories(

	../../src
) 
file(GLOB GRAFICO src/*.cpp src/*/*.cpp)
# terceros/*/*.cpp
add_library(motor_grafico_gl SHARED ${GRAFICO})
#target_link_libraries( motor_grafico_gl  ${CONAN_LIBS} )
target_link_libraries(motor_grafico_gl motor_grafico modulos)
if(WIN32)
	target_link_libraries( motor_grafico_gl OpenGL32.lib Glu32.lib)
elseif(UNIX)
	
endif()
