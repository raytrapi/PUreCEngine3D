cmake_minimum_required(VERSION 3.0.0)

project(2dMotorGame)
find_program(conan conan)
execute_process(COMMAND ${conan} install -s build_type=${CMAKE_BUILD_TYPE} ${CMAKE_CURRENT_SOURCE_DIR})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup()

include_directories(
   src
	${CONAN_INCLUDE}
) 
file(GLOB CODIGO src/*.cpp)
if(WIN32)
	file(GLOB CODIGOWIN src/windows/*.cpp)
	add_executable(2dMotorGame WIN32 ${CODIGO} ${CODIGOWIN} )
else()
	add_executable(2dMotorGame ${CODIGO})
endif()


target_link_libraries( 2dMotorGame  ${CONAN_LIBS})
if(WIN32)
	add_definitions(-D_AFXDLL)
	set(CMAKE_MFC_FLAG 2)

	target_link_libraries( 2dMotorGame OpenGL32.lib)
elseif(UNIX)
	
endif()
