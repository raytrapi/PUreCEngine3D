#add_subdirectory("extensiones") 

add_subdirectory("node_editors") 



file(GLOB MIOS src/*.h  "src/interfaceControl.cpp") 
#
##file(GLOB MIOS *.cpp */*.cpp)
add_library(pc_interface STATIC ${MIOS} ) 
set_property(TARGET pc_interface PROPERTY CXX_STANDARD 23)
target_link_libraries(pc_interface  pc_imgui_node)
 