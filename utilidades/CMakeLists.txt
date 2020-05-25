include_directories(
   log
) 

add_library(utilidades "SHARED"  log/log.cpp )
set_target_properties(utilidades PROPERTIES
	COMPILE_DEFINITIONS EXPORTAR_UTILIDADES
   PUBLIC_HEADER utiles/utilidades.h )
#target_link_libraries( utilidades  ${Boost_LIBRARIES})
target_link_libraries( utilidades  ${CONAN_LIBS})
