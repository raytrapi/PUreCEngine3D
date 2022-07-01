include_directories(
   ../utilidades/log
   ../utilidades/global
   ../modules/graphic
   ../modules/src
   ../graphics/src
   ../vendors/freetype/include
   src
)    
 
file(GLOB CODIGO modulos/*/*.cpp src/*.cpp) 

add_library(components SHARED ${CODIGO})
set_property(TARGET components PROPERTY CXX_STANDARD 20)
target_link_libraries( components  ${CONAN_LIBS} utils modules)
set_target_properties(components PROPERTIES
	COMPILE_DEFINITIONS EXPORTAR_COMPONENTE
    PUBLIC_HEADER src/components.h )

