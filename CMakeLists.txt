cmake_minimum_required( VERSION 2.8 )

## Load CMAKE configuration from environment variables
set( CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH} )
set( CMAKE_PREFIX_PATH $ENV{CMAKE_PREFIX_PATH} )

## Set global variables
set ( PROJECT_NAME_ "lucidy-engine" )
set ( OS_TARGET_ "Windows" ) # Choose between "Linux" and "Windows"
set ( AT_TARGET_ "x64" ) # Choose between "x64" and "x86"

## Specify a project name
project( ${PROJECT_NAME_} )
                       
set( __LIB_PATH "" )
set( __BIN_PATH "" )

set( __GLEW_LIB_NAME "glew32s.lib" )
set( __GLFW_LIB_NAME "libglfw3.a" )

if (OS_TARGET_ MATCHES "Windows")

  set( __BIN_PATH ${PROJECT_SOURCE_DIR}/build/windows/bin )

  if (AT_TARGET_ MATCHES "x64")
    set( __LIB_PATH ${PROJECT_SOURCE_DIR}/lib/windows/x64 )
  endif()

  if (AT_TARGET_ MATCHES "x86")
    set( __LIB_PATH ${PROJECT_SOURCE_DIR}/lib/windows/x86 )
    add_definitions(-D__CYGWIN__)
  endif()

endif()

if (OS_TARGET_ MATCHES "Linux")

  set( __BIN_PATH ${PROJECT_SOURCE_DIR}/build/linux/bin )
  set( __GLEW_LIB_NAME "libGLEW.a" )
  set( __GLFW_LIB_NAME "libglfw3.a" )

  if (AT_TARGET_ MATCHES "x64")
    set( __LIB_PATH ${PROJECT_SOURCE_DIR}/lib/linux/x64 )

  endif()

  if (AT_TARGET_ MATCHES "x86")
    set( __LIB_PATH ${PROJECT_SOURCE_DIR}/lib/linux/x86 )
  endif()

endif()


## Install the executable in this path
set(EXECUTABLE_OUTPUT_PATH ${__BIN_PATH})

## Install libraries (if any) in this path
set(LIBRARY_OUTPUT_PATH ${__LIB_PATH})

## Set global definitions to be used in c++
add_definitions(-DGLEW_STATIC)
add_definitions(-DSANDBOX_PATH="${PROJECT_SOURCE_DIR}/src/")

## Link Subdirectory 
add_subdirectory(${PROJECT_SOURCE_DIR}/src ${__BIN_PATH})
