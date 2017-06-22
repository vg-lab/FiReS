# Include directories
include_directories(
  ${PROJECT_SOURCE_DIR}/
  ${PROJECT_BINARY_DIR}
)

add_executable( FiReSProperties properties.cpp )
target_link_libraries( FiReSProperties FiReS )

add_executable( FiReSSearchScalar searchScalar.cpp )
target_link_libraries( FiReSSearchScalar FiReS )

add_executable( FiReSSearchLargeNumberOfObjects searchLargeNumberOfObjects.cpp)
target_link_libraries( FiReSSearchLargeNumberOfObjects FiReS)

add_executable( FiReSFilter filter.cpp )
target_link_libraries( FiReSFilter FiReS )

add_executable( FiReSSort sort.cpp )
target_link_libraries( FiReSSort FiReS )

add_executable( FiReSAggregate aggregate.cpp )
target_link_libraries( FiReSAggregate FiReS )

add_executable( FiReSTasks tasks.cpp )
target_link_libraries( FiReSTasks FiReS )

add_executable( FiReSObserver observer.cpp )
target_link_libraries( FiReSObserver FiReS )

add_executable( FiReSDependencies dependencies.cpp )
target_link_libraries( FiReSDependencies FiReS )

add_executable( FiReSCaster caster.cpp )
target_link_libraries( FiReSCaster FiReS )
