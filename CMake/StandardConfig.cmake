


# Default build type is Debug 
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Install dirs
set(INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include)
set(INSTALL_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib)
set(INSTALL_CMAKE_DIR ${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}/CMake)

# Include directories
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/ 
  ${CMAKE_CURRENT_BINARY_DIR}
) 

# Configure file 
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/config.h"
)
