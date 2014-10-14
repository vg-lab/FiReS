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
set(fires_VERSION_MAJOR 0)
set(fires_VERSION_MINOR 1)
set(fires_VERSION_PATCH 0)
set(fires_VERSION
    ${fires_VERSION_MAJOR}.${fires_VERSION_MINOR}.${fires_VERSION_PATCH})

# Standard configs like version, debug as default
include(StandardConfig)

# Custom flags for Release and Debug
set(CMAKE_CXX_FLAGS 
  "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wno-unknown-pragmas")
set(CMAKE_CXX_FLAGS_DEBUG 
  "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")


# Build library
add_library (fires SHARED
${CMAKE_CURRENT_SOURCE_DIR}/fires/Comparer.cpp  
${CMAKE_CURRENT_SOURCE_DIR}/fires/FeatureFloatPtrComparer.cpp  
${CMAKE_CURRENT_SOURCE_DIR}/fires/FeatureFloatPtr.cpp  
${CMAKE_CURRENT_SOURCE_DIR}/fires/Object.cpp  
${CMAKE_CURRENT_SOURCE_DIR}/fires/System.cpp
)
set_target_properties(fires
  PROPERTIES VERSION ${fires_VERSION} SOVERSION ${fires_VERSION}
)

# Install rules
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
