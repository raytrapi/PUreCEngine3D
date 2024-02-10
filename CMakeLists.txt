cmake_minimum_required(VERSION 3.5.0)
  
project(2dMotorGame) 

find_program(conan conan)

execute_process(COMMAND ${conan} install -s build_type=${CMAKE_BUILD_TYPE} ${CMAKE_CURRENT_SOURCE_DIR} --build=missing)# --build=libpng --build=zlib --build=glfw --build=imgui --build=openal)

#execute_process(COMMAND ${conan} install -s build_type=${CMAKE_BUILD_TYPE} ${CMAKE_CURRENT_SOURCE_DIR} -of ${CMAKE_CURRENT_BINARY_DIR} --build=missing)# --build=libpng --build=zlib --build=glfw --build=imgui --build=openal)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)  
  
conan_basic_setup() 
 
     

#cmake_dependent_option(USE_STATIC_MSVC_RUNTIME_LIBRARY "Use the static MSVC runtime library" ON "MSVC;NOT WINDOWS_STORE" OFF)
if (("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows" OR "${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsStore") AND NOT MINGW)
	# Set runtime library
	if (USE_STATIC_MSVC_RUNTIME_LIBRARY)
		set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	else()
		set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
	endif()
endif() 
#El supervisor servirá para generar la reflexión de las clases 
add_subdirectory("utilidades/supervisor") 

option(JOLT_PHYSICS "Activamos las físicas de Jolt" ON) 

#add_subdirectory("vendors/openal-soft") 
add_subdirectory("vendors/freetype") 
if(JOLT_PHYSICS) 
    #add_subdirectory("vendors/JoltPhysics/Build") 
    #set(PHYSICS_REPO_ROOT "vendors/JoltPhysics/")
    #include(vendors/JoltPhysics/Jolt/Jolt.cmake)
    
endif() 

add_subdirectory("utilidades") 
add_subdirectory("modules") 
add_subdirectory("components") 
add_subdirectory("lib")

  

add_subdirectory("audio")
#[[if(WIN32)
	add_custom_command(
    TARGET modulos POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/modulos.dll
        ${CMAKE_BINARY_DIR}/bin/modulos
   )
elseif(UNIX)
	add_custom_command(
    TARGET modulos POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/bin/modulos.so
        ${CMAKE_BINARY_DIR}/bin/modulos
    )
endif()]]

add_subdirectory("graphics")
add_subdirectory("physics")

include_directories( 
   src
   modules/src
   utilidades/librerias
	utilidades/log
   utilidades/files 
   utilidades/timer  
   utilidades/project
   ../utilidades/supervisor/src 
   utilidades
) 

file(GLOB CODIGO src/*.cpp utilidades/librerias/compile.cpp src/proyectos/*.cpp)# graphics/src/renderable/renderable.h 
#file(GLOB MOTOR src/Motor/*/*.cpp src/Motor/*.cpp) 

#file(GLOB MOTORGL src/terceros/*/*.cpp) 
 
if(WIN32)
	#file(GLOB CODIGOWIN src/windows/*/*.cpp src/windows/*.cpp)
	add_executable(2dMotorGame WIN32 ${CODIGO} )#${CODIGOWIN})
     
else()
	add_executable(2dMotorGame ${CODIGO})
endif()


set_property(TARGET 2dMotorGame PROPERTY CXX_STANDARD 23)

target_link_libraries( 2dMotorGame utils motor_grafico  components modules globals) 


#add_subdirectory("ejemplos")

set(GUI_ONLY_BINARIES 2dMotorGame)

if (MSVC)
    # Tell MSVC to use main instead of WinMain for Windows subsystem executables
    set_target_properties(${GUI_ONLY_BINARIES} PROPERTIES
                         LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()
  
add_custom_command(
    TARGET 2dMotorGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_HOME_DIRECTORY}/src/proyectos/compiler
        ${CMAKE_BINARY_DIR}/bin/
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_HOME_DIRECTORY}/src/proyectos/defproj
        ${CMAKE_BINARY_DIR}/bin/
   )


#make_directory(${CMAKE_CURRENT_BINARY_DIR}/bin/resources)

file(COPY ${CMAKE_HOME_DIRECTORY}/resources DESTINATION  ${CMAKE_CURRENT_BINARY_DIR}/bin)



message("Copy inlcude imgui from ${CONAN_IMGUI_ROOT} to ${CMAKE_HOME_DIRECTORY}")
file(COPY ${CONAN_IMGUI_ROOT}/include DESTINATION  ${CMAKE_HOME_DIRECTORY}/vendors/imgui)
