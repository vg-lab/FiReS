# Include directories
include_directories(
  ${PROJECT_SOURCE_DIR}/
  ${PROJECT_BINARY_DIR}
)

add_executable( firesProperties properties.cpp )
target_link_libraries( firesProperties fires )

add_executable( firesSearchScalar searchScalar.cpp )
target_link_libraries( firesSearchScalar fires )

add_executable( firesSearchLargeNumberOfObjects searchLargeNumberOfObjects.cpp)
target_link_libraries( firesSearchLargeNumberOfObjects fires)

add_executable( firesFilter filter.cpp )
target_link_libraries( firesFilter fires )

add_executable( firesSort sort.cpp )
target_link_libraries( firesSort fires )

add_executable( firesAggregate aggregate.cpp )
target_link_libraries( firesAggregate fires )

add_executable( firesTasks tasks.cpp )
target_link_libraries( firesTasks fires )
