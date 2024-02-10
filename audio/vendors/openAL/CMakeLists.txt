
include_directories(
	src
   ../../src 
   ../../../utilidades/log
   ../../../utilidades/timer
   ../../../modules/src
   ../../../vendors/openal-soft/include
) 

file(GLOB CODIGO src/*.cpp src/*/*.cpp)
add_library(audioAL SHARED ${CODIGO})

set_property(TARGET audioAL PROPERTY CXX_STANDARD 23)
target_link_libraries(audioAL utils modules audio ${CONAN_LIBS})#OpenAL32)

if(WIN32)
	add_custom_command(
    TARGET audioAL POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/audioAL.dll
        ${CMAKE_BINARY_DIR}/bin/modulos
   )
elseif(UNIX)
	add_custom_command(
    TARGET audioAL POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/audioAL.so
        ${CMAKE_BINARY_DIR}/bin/modulos
    )
endif()
