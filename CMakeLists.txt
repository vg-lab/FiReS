# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   FiReS - Filtering and Retrieval System
#   2014 (c) GMRV / Universidad Rey Juan Carlos
#   gmrv@gmrv.es
#   www.gmrv.es
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
project(fires)
cmake_minimum_required(VERSION 2.8)


# Add CMake dir to the module path
list(APPEND CMAKE_MODULE_PATH 
  ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

# Version numbers
set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 1)
set(${PROJECT_NAME}_VERSION_PATCH 0)
set(${PROJECT_NAME}_VERSION
    ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH})

# Default build type is Debug 
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

# Custom flags for Release and Debug
set(CMAKE_CXX_FLAGS 
  "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wno-unknown-pragmas")
set(CMAKE_CXX_FLAGS_DEBUG 
  "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

# Install dirs
set(INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include)
set(INSTALL_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib)
set(INSTALL_CMAKE_DIR ${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}/CMake)

# Find header files to install 
file(GLOB DEPLOY_FILES_AND_DIRS 
"${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/*"
)
foreach(ITEM ${DEPLOY_FILES_AND_DIRS})
   if( IS_DIRECTORY "${ITEM}" )
      list( APPEND DIRS_TO_DEPLOY "${ITEM}" )
   else()
     get_filename_component(FILE_EXT "${ITEM}" "EXT")
     if( FILE_EXT STREQUAL ".h" )
       list( APPEND FILES_TO_DEPLOY "${ITEM}" )
     endif()
   endif()
endforeach()
# # # # # # # # # # # # # # # # # # # # # #  # # # # # # # # # # # # # # #

# Configure file 
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/config.h"
  )

# Build library
add_library (${PROJECT_NAME} SHARED
${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Comparer.cpp  
${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/FeatureFloatPtrComparer.cpp  
${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/FeatureFloatPtr.cpp  
${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Object.cpp  
${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/System.cpp

)
set_target_properties(${PROJECT_NAME}
  PROPERTIES VERSION ${${PROJECT_NAME}_VERSION} SOVERSION ${${PROJECT_NAME}_VERSION}
)

# Install rules
include(InstallLibrary)

# Doxygen documentation generation
include(Doxygen)

# Add examples subdirectory
add_subdirectory(examples)

# Export library
include(ExportLibrary)
