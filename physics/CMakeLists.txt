add_subdirectory("physics 1.0")
#if(JOLT_PHYSICS) 
	option(JPH_ENABLE_ASSERTS "Activamos las aserciones de Jolt" ON) 

	add_subdirectory("jolt")
#endif()