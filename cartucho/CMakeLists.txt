
include_directories(
   ../utilidades/log
	../src
) 

file(GLOB CODIGO src/*.cpp src/*/*.cpp)

add_library(cartucho SHARED ${CODIGO})
target_link_libraries( cartucho  ${CONAN_LIBS} utilidades modulos)
set_target_properties(cartucho PROPERTIES
	COMPILE_DEFINITIONS EXPORTAR_MODULO_CARTUCHO
    PUBLIC_HEADER src/cartucho.h )

#add_subdirectory("terceros/opengl")
