# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   FiReS - Filtering and Retrieval System
#   2014 (c) GMRV / Universidad Rey Juan Carlos
#   gmrv@gmrv.es
#   www.gmrv.es
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
cmake_minimum_required(VERSION 2.8)
project(fires)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

include(GitExternal)

# fires version
set(LAST_RELEASE 0.0.0)
set(VERSION_MAJOR "0")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")
set(VERSION_ABI 1)

# description
set(FIRES_DESCRIPTION "FiReS - Filter and retrieval System")
set(COMMON_PROJECT_DOMAIN gmrv.es)


option(WITH_VMMLIB "WITH_VMMLIB" ON)
option(WITH_OPENMP "WITH_OPENMP" ON)


include(Common)
include(FindPackages) 

# library subdirectory 
add_subdirectory(fires)

# tests subdirectory 
add_subdirectory(tests)

# examples subdirectory
add_subdirectory(examples)

include(CPackConfig)
include(DoxygenRule)


