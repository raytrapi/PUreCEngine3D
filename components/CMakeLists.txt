include_directories(
   ../utilidades/log
   ../utilidades/global
   ../utilidades/supervisor/src
   ../utilidades
   ../modules/graphic
   ../modules/src
   ../graphics/src
   ../vendors/freetype/include

   src
)   
file(GLOB RENDERIZABLES 
   modulos/renderables/objects/object.cpp 
   modulos/renderables/objects/pixel.cpp 
   modulos/renderables/objects/img.cpp 
   modulos/renderables/objects/renderable.cpp 
   modulos/renderables/objects/cube.cpp  
   modulos/renderables/objects/mesh.cpp
   modulos/renderables/objects/line.cpp 
   modulos/renderables/objects/text.cpp 
   modulos/renderables/resources/material.cpp 
   modulos/renderables/resources/texture.cpp 
)  
  
file(GLOB CODIGO  modulos/*/*.cpp src/*.cpp ../graphics/terceros/opengl4/src/imgui/imgui_controles.cpp ../utilidades/supervisor/src/reflexivo.cpp) 

#Lo quitaremos y cambiaremos por una carga dinámica
file(GLOB VENDORS vendors/mapsGenerator/*.cpp ../graphics/terceros/opengl4/src/imgui/controles/imgui_curve.cpp)

add_library(components SHARED ${CODIGO} ${RENDERIZABLES} ${VENDORS})
set_property(TARGET components PROPERTY CXX_STANDARD 23)
target_link_libraries( components  ${CONAN_LIBS} utils modules freetype globals imports)
set_target_properties(components PROPERTIES
	COMPILE_DEFINITIONS EXPORTAR_COMPONENTE 
    PUBLIC_HEADER src/components.h ) 


#add_subdirectory(vendors)