
include_directories(
   src
)  

file(GLOB CODIGO src/*.cpp)
 
add_library(audio ${CODIGO})
set_property(TARGET audio PROPERTY CXX_STANDARD 23)
target_link_libraries( audio  ${CONAN_LIBS} utils modules)



set_target_properties(audio PROPERTIES
	COMPILE_DEFINITIONS EXPORTAR_AUDIO
    PUBLIC_HEADER src/audiosBase.h 
)


add_subdirectory("vendors")

