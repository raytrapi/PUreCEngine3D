include_directories(
   log
) 

add_library(utilidades "SHARED"  log/log.cpp  nucleo/screen.cpp timer/timer.cpp)
set_target_properties(utilidades PROPERTIES
	COMPILE_DEFINITIONS EXPORTAR_UTILIDADES
   PUBLIC_HEADER utiles/utilidades.h )
#target_link_libraries( utilidades  ${Boost_LIBRARIES})
target_link_libraries( utilidades  ${CONAN_LIBS})

#[[if(WIN32)
	add_custom_command(
    TARGET utilidades POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/utilidades.dll
        ${CMAKE_BINARY_DIR}/bin/modulos
   )
elseif(UNIX)
	add_custom_command(
    TARGET utilidades POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/utilidades.so
        ${CMAKE_BINARY_DIR}/bin/modulos
    )
endif()]]