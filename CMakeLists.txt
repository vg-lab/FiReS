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

# Version numbers
set(fires_VERSION_MAJOR 0)
set(fires_VERSION_MINOR 1)
set(fires_VERSION_PATCH 0)
set(fires_VERSION
    ${fires_VERSION_MAJOR}.${fires_VERSION_MINOR}.${fires_VERSION_PATCH})

# Default build type is Debug 
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)


# Custom flags for Release and Debug
set(CMAKE_CXX_FLAGS 
  "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wno-unknown-pragmas")
set(CMAKE_CXX_FLAGS_DEBUG 
  "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")


include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/ 
  ${CMAKE_CURRENT_BINARY_DIR}
) 


# # # # # # # # # # # # # # # # # # # #  # # # # # # # # # # # # # # # # #
# Find files to install 
# # # # # # # # # # # # # # # # # # # # ## # # # # # # # # # # # # # # # # 
file(GLOB DEPLOY_FILES_AND_DIRS 
"${CMAKE_CURRENT_SOURCE_DIR}/fires/*"
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
install( FILES ${FILES_TO_DEPLOY} DESTINATION include/fires )
install( FILES ${CMAKE_CURRENT_BINARY_DIR}/fires/FiresConfig.h 
  DESTINATION include/fires )
install( DIRECTORY ${DIRS_TO_DEPLOY} DESTINATION include/fires )
# # # # # # # # # # # # # # # # # # # # # #  # # # # # # # # # # # # # # #


# Configure file 
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/fires/FiresConfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/fires/FiresConfig.h"
  )

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

install(TARGETS fires DESTINATION lib)


# Doxygen documentation generation
find_package(Doxygen)
if(DOXYGEN_FOUND)

  execute_process(
    COMMAND ${CMAKE_COMMAND} -E make_directory "doc"
    RESULT_VARIABLE nok ERROR_VARIABLE error
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
  if(nok)
    message(FATAL_ERROR "Error making building dir in " 
      ${CMAKE_CURRENT_BINARY_DIR}": ${nok}\n")
  endif()

  configure_file(${CMAKE_SOURCE_DIR}/doc/Doxyfile
    ${CMAKE_BINARY_DIR}/doc/Doxyfile @ONLY)


  add_custom_target(doc
    COMMAND ${DOXYGEN_EXECUTABLE} 
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/doc"
    )

endif()


add_subdirectory(examples)
