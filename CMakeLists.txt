cmake_minimum_required( VERSION 3.1 )

project( GLFW-CMake-starter )

find_package( OpenGL REQUIRED )

include_directories( ${OPENGL_INCLUDE_DIRS} )

include_directories( glad/include/ )

# Useful CMake options for Qt projects
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

add_library( glad /home/user/projects/code/cpp/GLFW-CMake-starter/glad/src/glad.c )
add_subdirectory( /home/user/projects/code/cpp/GLFW-CMake-starter/glfw/glfw/glfw )

set( GLFW-CMAKE-STARTER-SRC
     main.cpp
     shader.cpp
     )
     
add_executable( GLFW-CMake-starter WIN32 ${GLFW-CMAKE-STARTER-SRC} )
target_link_libraries( GLFW-CMake-starter ${OPENGL_LIBRARIES} glfw glad )
