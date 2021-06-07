
include_directories(
   log
   ../graphics/src/renderable
) 

add_library(utils "SHARED"  log/log.cpp  global/screen.cpp timer/timer.cpp global/input.cpp global/mouse.cpp files/filesControl.cpp timer/watchdog.cpp )

set_target_properties(utils PROPERTIES
	COMPILE_DEFINITIONS EXPORTAR_UTILIDADES
   PUBLIC_HEADER utils/utils.h )
#target_link_libraries( utilidades  ${Boost_LIBRARIES})
set_property(TARGET utils PROPERTY CXX_STANDARD 20)
target_link_libraries( utils  ${CONAN_LIBS})

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