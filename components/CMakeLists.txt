
include_directories(
   ../utilidades/log
   ../modules/graphic
   ../modules/src
) 

file(GLOB CODIGO modulos/*/*.cpp src/*.cpp)

add_library(components SHARED ${CODIGO})
target_link_libraries( components  ${CONAN_LIBS} utils modules)
set_target_properties(components PROPERTIES
	COMPILE_DEFINITIONS EXPORTAR_COMPONENTE
    PUBLIC_HEADER src/components.h )

