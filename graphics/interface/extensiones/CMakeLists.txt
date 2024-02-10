

file(GLOB MIOS *.cpp)
add_library(pc_imgui_ext STATIC ${MIOS} ) 
set_property(TARGET pc_imgui_ext PROPERTY CXX_STANDARD 23)
