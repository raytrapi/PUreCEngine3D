
#include_directories(
#	
#) 
          
file(GLOB COD *.cpp)
add_library(Maps_Gen SHARED ${COD} ) 
#add_library(Maps_Gen STATIC ${COD} ) 
  
set_property(TARGET Maps_Gen PROPERTY CXX_STANDARD 23)
target_link_libraries(Maps_Gen utils motor_grafico )
 
    
#if(WIN32)
#	#target_link_libraries( Maps_Gen ${CONAN_LIBS} )
#	add_custom_command(
#    TARGET Maps_Gen POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        ${CMAKE_BINARY_DIR}/bin/Maps_Gen.dll
#        ${CMAKE_BINARY_DIR}/bin/ 
#   )
#elseif(UNIX)
#	add_custom_command(
#    TARGET Maps_Gen POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        ${CMAKE_BINARY_DIR}/bin/Maps_Gen.so
#        ${CMAKE_BINARY_DIR}/bin/
#    )
#endif()
