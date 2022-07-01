
include_directories(
   log
   ../graphics/src/renderable
) 

add_library(utils SHARED  log/log.cpp  timer/timer.cpp 
            files/filesControl.cpp timer/watchdog.cpp  
            utiles/string.cpp  log/logFile.cpp 
            )
			#librerias/compile.cpp librerias/dll.cpp
 
set_target_properties(utils PROPERTIES
	COMPILE_DEFINITIONS EXPORTAR_UTILIDADES 
   PUBLIC_HEADER utils/utils.h )
#target_link_libraries( utilidades  ${Boost_LIBRARIES})
set_property(TARGET utils PROPERTY CXX_STANDARD 20)
target_link_libraries( utils  ${CONAN_LIBS})
 

add_library(globals SHARED  global/screen.cpp 
            global/input.cpp global/mouse.cpp  
            global/global.cpp)
set_target_properties(globals PROPERTIES
	COMPILE_DEFINITIONS EXPORTAR_UTILIDADES 
   PUBLIC_HEADER utils/global.h )
#target_link_libraries( utilidades  ${Boost_LIBRARIES})
set_property(TARGET globals PROPERTY CXX_STANDARD 20)
target_link_libraries( globals  ${CONAN_LIBS})
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