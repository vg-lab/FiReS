# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   FiReS - Filter, Retrieval and Search
#   2014 - 2016 (c) GMRV / Universidad Rey Juan Carlos
#   gmrv@gmrv.es
#   www.gmrv.es
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(FiReS VERSION 0.1.0 )
set(FiReS_VERSION_ABI 1)

list(APPEND CMAKE_MODULE_PATH
  ${PROJECT_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

include(GitExternal)


include(Common)

# description
set(FIRES_DESCRIPTION "FiReS - Filter, Retrieval and Search")
set(COMMON_PROJECT_DOMAIN gmrv.es)

common_find_package( Boost REQUIRED COMPONENTS unit_test_framework )
common_find_package( OpenMP )
common_find_package_post( )

set( FIRES_DEPENDENT_LIBRARIES Boost )

add_subdirectory( fires )
add_subdirectory( tests )
add_subdirectory( examples )

include( CPackConfig )
include( DoxygenRule )
