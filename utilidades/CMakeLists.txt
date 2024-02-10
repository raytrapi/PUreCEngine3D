
include_directories(
   log
   ../graphics/src/renderable
   project
   errors 
   ../modules/graphyc
) 
 
add_library(utils SHARED  log/log.cpp  timer/timer.cpp 
            files/filesControl.cpp timer/watchdog.cpp  
            utiles/string.cpp  log/logFile.cpp 
            project/serializer/serializer.cpp project/serializer/deserializer.cpp
            utiles/handler.cpp utiles/pointer.cpp project/genericFile.cpp 
            math/math.cpp
            ) 
			#librerias/compile.cpp librerias/dll.cpp
  
set_target_properties(utils PROPERTIES
	COMPILE_DEFINITIONS EXPORTAR_UTILIDADES 
   PUBLIC_HEADER utils/utils.h )
#target_link_libraries( utilidades  ${Boost_LIBRARIES})
set_property(TARGET utils PROPERTY CXX_STANDARD 23) 
target_link_libraries( utils  ${CONAN_LIBS})
  
  
add_library(globals SHARED  global/screen.cpp  
            global/input.cpp global/mouse.cpp  
            global/global.cpp project/projectFile.cpp
            project/levelFile.cpp project/entityFile.cpp
            project/componentFile.cpp global/node.cpp 
            
)   
set_target_properties(globals PROPERTIES
	COMPILE_DEFINITIONS EXPORTAR_UTILIDADES 
   PUBLIC_HEADER utils/global.h )
#target_link_libraries( utilidades  ${Boost_LIBRARIES})
set_property(TARGET globals PROPERTY CXX_STANDARD 23)
target_link_libraries( globals  ${CONAN_LIBS} utils )


file(GLOB CARGAMODELOS imports/model.cpp imports/obj.cpp imports/fbx.cpp ../vendors/OpenFBX/src/ofbx.cpp ../vendors/OpenFBX/src/miniz.c)
add_library(imports SHARED   ${CARGAMODELOS} )
set_property(TARGET imports PROPERTY CXX_STANDARD 23) 
target_link_libraries(imports  ${CONAN_LIBS} utils  globals)
set_target_properties(imports PROPERTIES
	COMPILE_DEFINITIONS EXPORTAR_UTILIDADES
    PUBLIC_HEADER src/imports.h ) 


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