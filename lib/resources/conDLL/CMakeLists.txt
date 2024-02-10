


include_directories(
   ../../../modules/src
) 

file(GLOB RES src/*.cpp src/*/*.cpp)
add_library(res_dll SHARED ${RES})

set_property(TARGET res_dll PROPERTY CXX_STANDARD 23)
target_link_libraries( res_dll utils modules ${CONAN_LIBS} )
#target_link_libraries( res_dll optimized libpng16d.lib)

if(WIN32)
   
	#target_link_libraries( mg_gl4 OpenGL32.lib Glu32.lib "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.lib")
	add_custom_command(
    TARGET res_dll POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/res_dll.dll
        ${CMAKE_BINARY_DIR}/bin/modulos
   )
elseif(UNIX)
	add_custom_command(
    TARGET res_dll POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/res_dll.so
        ${CMAKE_BINARY_DIR}/bin/modulos
    )
endif()