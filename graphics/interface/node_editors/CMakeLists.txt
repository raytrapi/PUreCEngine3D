include_directories(
	../../../vendors/imgui-node-editor/
)  
file(GLOB NODESRC ../../../vendors/imgui-node-editor/*.cpp)
file(GLOB MIOS *.cpp)# */*.cpp)
add_library(pc_imgui_node STATIC ${NODESRC} ${MIOS} ) 
set_property(TARGET pc_imgui_node PROPERTY CXX_STANDARD 23)

target_link_libraries(pc_imgui_node )#pc_imgui_ext)
 
    
#if(WIN32)
#	#target_link_libraries( mg_gl4 OpenGL32.lib Glu32.lib "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.lib")
#    target_link_libraries( gl_imgui_node ${CONAN_LIBS} )
#	add_custom_command(
#    TARGET gl_imgui_node POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        ${CMAKE_BINARY_DIR}/bin/gl_imgui_node.dll
#        ${CMAKE_BINARY_DIR}/bin/modulos
#   )
#elseif(UNIX)
#	add_custom_command(
#    TARGET gl_imgui_node POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        ${CMAKE_BINARY_DIR}/bin/gl_imgui_node.so
#        ${CMAKE_BINARY_DIR}/bin/modulos
#    )
#endif()

