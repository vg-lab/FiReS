

# Include directories 
include_directories(
  ${CMAKE_SOURCE_DIR}/ 
  ${CMAKE_BINARY_DIR}
) 

add_executable(example1 example1.cpp)
target_link_libraries(example1 fires)

