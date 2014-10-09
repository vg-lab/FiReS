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

set(INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include)
set(INSTALL_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib)
set(INSTALL_CMAKE_DIR ${CMAKE_INSTALL_PREFIX}/share/fires/CMake)

install(TARGETS fires 
  EXPORT firesTargets
  DESTINATION ${INSTALL_LIB_DIR}
  COMPONENT dev)


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


# Add exaples subdirectory
add_subdirectory(examples)



# Add all targets to the build-tree export set
export(TARGETS fires
  FILE "${PROJECT_BINARY_DIR}/firesTargets.cmake")
 
# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE fires)
 
# Create the firesConfig.cmake and firesConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(firesConfig.cmake.in
  "${PROJECT_BINARY_DIR}/firesConfig.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${FOOBAR_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(firesConfig.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/firesConfig.cmake" @ONLY)
# ... for both
configure_file(firesConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/firesConfigVersion.cmake" @ONLY)
 
# Install the FooBarConfig.cmake and FooBarConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/firesConfig.cmake"
  "${PROJECT_BINARY_DIR}/firesConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)
 
# Install the export set for use with the install-tree
install(EXPORT firesTargets DESTINATION
  "${INSTALL_CMAKE_DIR}" COMPONENT dev)
