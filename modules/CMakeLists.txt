
include_directories(
   ../utilidades/log
   ../utilidades/files
   ../utilidades/global
   ../vendors/glad/include
   ./src
)  

file(GLOB CODIGO tape/*.cpp resources/*.cpp audio/*.cpp graphic/*.cpp physics/*.cpp)

add_library(modules SHARED src/module.cpp ${CODIGO} )
set_property(TARGET modules PROPERTY CXX_STANDARD 20)

target_link_libraries( modules  ${CONAN_LIBS} utils globals)
set_target_properties(modules PROPERTIES
	COMPILE_DEFINITIONS EXPORTAR_MODULO
    PUBLIC_HEADER src/modules.h )

make_directory(${CMAKE_BINARY_DIR}/bin/modulos)
#add_subdirectory("terceros/opengl")
