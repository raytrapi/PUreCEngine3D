
include_directories(
	../../cartucho/src
   ../../utilidades/timer
   ../../utilidades/nucleo
   ../../graphics/src/renderable
   
) 
file(GLOB CODIGO src/*.cpp src/*/*.cpp)
# terceros/*/*.cpp
add_library(hormiguero SHARED ${CODIGO})
target_link_libraries(hormiguero cartucho modulos motor_grafico)

if(WIN32)
	
	add_custom_command(
    TARGET hormiguero POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/hormiguero.dll
        ${CMAKE_BINARY_DIR}/bin/modulos
   )
elseif(UNIX)
	add_custom_command(
    TARGET hormiguero POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/hormiguero.so
        ${CMAKE_BINARY_DIR}/bin/modulos
    )
endif()


