# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   FiReS - Filter, Retrieval and Search
#   2014 - 2017 (c) GMRV / URJC / UPM
#   gmrv@gmrv.es
#   www.gmrv.es
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
cmake_minimum_required( VERSION 3.1 FATAL_ERROR )
project( FiReS VERSION 0.1.6 )
set( FiReS_VERSION_ABI 4 )

list( APPEND CMAKE_MODULE_PATH
  ${PROJECT_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common )

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/CMake/common/Common.cmake)
  message(FATAL_ERROR "CMake/common missing, run: git submodule update --init")
endif()

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Debug )
endif( NOT CMAKE_BUILD_TYPE )

include( Common )

set( FIRES_DEB_DEPENDS libboost-dev )

set( FIRES_DESCRIPTION "FiReS - Filter, Retrieval and Search" )
set( FIRES_LICENSE LGPL )
set( FIRES_MAINTAINER "Pablo Toharia <pablo.toharia@upm.es>" )
set( COMMON_PROJECT_DOMAIN es.gmrv )

common_find_package( Boost REQUIRED COMPONENTS unit_test_framework )
common_find_package( OpenMP )
common_find_package_post( )

set( FIRES_DEPENDENT_LIBRARIES Boost )

add_subdirectory( fires )
add_subdirectory( tests )
add_subdirectory( examples )

set( DOCS README.md LICENSE.txt )
install( FILES ${DOCS} DESTINATION share/fires COMPONENT dev )

set( DOXYGEN_MAINPAGE_MD README.md )
set( DOXYGEN_EXTRA_INPUT ${PROJECT_SOURCE_DIR}/README.md )
include( DoxygenRule )

include( CPackConfig )
include( CTest )
