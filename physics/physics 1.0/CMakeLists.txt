
include_directories(
   ../../utilidades/log
   ../../modules/physics
   ../../components/modulos
   ../../components/src/
)  

file(GLOB CODIGO src/*.cpp)

add_library(physics_1_0 SHARED ${CODIGO} )
set_property(TARGET physics_1_0 PROPERTY CXX_STANDARD 23)
target_link_libraries( physics_1_0 modules components)
set_target_properties(physics_1_0 PROPERTIES
	COMPILE_DEFINITIONS EXPORTAR_PHYSICS
    PUBLIC_HEADER src/physics.h )


 if(WIN32)
	#target_link_libraries( mg_gl4 OpenGL32.lib Glu32.lib "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.lib")
    add_custom_command(
    TARGET physics_1_0 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/physics_1_0.dll
        ${CMAKE_BINARY_DIR}/bin/modulos
   )
elseif(UNIX)
	add_custom_command(
    TARGET physics_1_0 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/physics_1_0.so
        ${CMAKE_BINARY_DIR}/bin/modulos
    )
endif()