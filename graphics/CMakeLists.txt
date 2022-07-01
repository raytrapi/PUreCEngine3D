
include_directories(
   ../utilidades/log
   ../utilidades/global
	../src
   ../modules/src
   ../modules/graphic
   ../vendors/freetype/include
   src 
   src/modelos_graficos
) 
   
   
file(GLOB GRAFICO terceros/imagenes/*.cpp)
file(GLOB RENDERIZABLES src/renderable/object.cpp 
   src/renderable/pixel.cpp 
   src/renderable/img.cpp 
   src/renderable/renderable.cpp 
   src/renderable/cube.cpp 
   src/renderable/mesh.cpp
   src/renderable/line.cpp 
   src/renderable/text.cpp
)
file(GLOB CARGAMODELOS src/modelos_graficos/model.cpp src/modelos_graficos/obj.cpp src/modelos_graficos/fbx.cpp ../vendors/OpenFBX/src/ofbx.cpp ../vendors/OpenFBX/src/miniz.c)
file(GLOB COLLIDER src/collider/*.cpp)
file(GLOB EXTRA src/log/logEntity.cpp)
# terceros/*/*.cpp
add_library(motor_grafico SHARED  ${RENDERIZABLES} ${GRAFICO} ${CARGAMODELOS} ${COLLIDER} ${EXTRA})
set_property(TARGET motor_grafico PROPERTY CXX_STANDARD 20) 
target_link_libraries(motor_grafico  ${CONAN_LIBS} utils modules components freetype)
set_target_properties(motor_grafico PROPERTIES
	COMPILE_DEFINITIONS EXPORTAR_MODULO_GRAFICO
    PUBLIC_HEADER src/motor.h ) 

     

#if(WIN32)
	#target_link_libraries( motor_grafico OpenGL32.lib Glu32.lib)
#elseif(UNIX)
	 
#endif()

#[[if(WIN32)
	add_custom_command(
    TARGET motor_grafico POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/motor_grafico.dll
        ${CMAKE_BINARY_DIR}/bin/modulos
   )
elseif(UNIX)
	add_custom_command(
    TARGET motor_grafico POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/motor_grafico.so
        ${CMAKE_BINARY_DIR}/bin/modulos
    )
endif()]]
 
#add_subdirectory("terceros/opengl")
add_subdirectory("terceros/opengl4") 
