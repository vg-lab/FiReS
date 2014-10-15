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

# Option to build with shared pointers or raw pointers
option(WITH_VMMLIB "WITH_VMMLIB" ON)
set(FIRES_WITH_VMMLIB 0)
if (WITH_VMMLIB)
  find_package(vmmlib)
  if (VMMLIB_FOUND)
    set(FIRES_WITH_VMMLIB 1)
  endif()
endif()


# Add CMake dir to the module path
list(APPEND CMAKE_MODULE_PATH 
  ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

# Version numbers
set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 1)
set(${PROJECT_NAME}_VERSION_PATCH 0)
set(${PROJECT_NAME}_VERSION
    ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH})

# Standard configs like version, debug as default
include(StandardConfig)

# Include vmmlib include dirs if needing
if (${FIRES_WITH_VMMLIB} MATCHES 1)
  include_directories(${VMMLIB_INCLUDE_DIRS})
endif()  


# Custom flags for Release and Debug
set(CMAKE_CXX_FLAGS 
  "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wno-unknown-pragmas")
set(CMAKE_CXX_FLAGS_DEBUG 
  "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")


# Build library
add_library (${PROJECT_NAME} SHARED
${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Comparer.cpp  
${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/FeatureFloatPtrComparer.cpp  
#${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/FeatureVectorPtrComparer.cpp  
${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/FeatureFloatPtr.cpp  
${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/FeaturePtr.cpp  
${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Object.cpp  
${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/System.cpp
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES VERSION ${${PROJECT_NAME}_VERSION} 
  SOVERSION ${${PROJECT_NAME}_VERSION}
)

# Find files to install 
file(GLOB DEPLOY_FILES_AND_DIRS 
"${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/*")

include(InstallLibrary)

# Doxygen documentation generation
include(Doxygen)

# Test subdirectory 
add_subdirectory(test)

# Examples subdirectory 
add_subdirectory(examples)

# Export library
include(ExportLibrary)
