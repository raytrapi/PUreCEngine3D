PROJECT(Supervisor)
set (CMAKE_CXX_STANDARD 23)
ADD_EXECUTABLE(supervisor src/main.cpp src/procesar.cpp src/reflexivo.cpp )

#add_custom_command(
#    TARGET supervisor POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#    ${CMAKE_BINARY_DIR}/utilidades/supervisor/supervisor.exe
#    ${CMAKE_BINARY_DIR}/bin
#) 