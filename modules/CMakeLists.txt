
include_directories(
   ../utilidades/log
   ../utilidades/files
 
) 

file(GLOB CODIGO graphic/*.cpp tape/*.cpp resources/*.cpp)

add_library(modules SHARED src/module.cpp ${CODIGO})
set_property(TARGET modules PROPERTY CXX_STANDARD 20)

target_link_libraries( modules  ${CONAN_LIBS} utils)
set_target_properties(modules PROPERTIES
	COMPILE_DEFINITIONS EXPORTAR_MODULO
    PUBLIC_HEADER src/modules.h )

make_directory(${CMAKE_BINARY_DIR}/bin/modulos)
#add_subdirectory("terceros/opengl")
