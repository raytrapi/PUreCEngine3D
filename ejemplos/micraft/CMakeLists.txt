
include_directories(
	../../modules/tape
   ../../utilidades/
   ../../graphics/src/renderable
   ../../components/src
   src
) 
file(GLOB CODIGO src/*.cpp src/*/*.cpp)
# terceros/*/*.cpp
add_library(minecraft SHARED ${CODIGO})
target_link_libraries(minecraft modules motor_grafico components)

if(WIN32)
	
	add_custom_command(
    TARGET minecraft POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/minecraft.dll
        ${CMAKE_BINARY_DIR}/bin/modulos
   )
elseif(UNIX)
	add_custom_command(
    TARGET minecraft POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/minecraft.so
        ${CMAKE_BINARY_DIR}/bin/modulos
    )
endif()


