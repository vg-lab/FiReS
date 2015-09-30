# Include directories
include_directories(
  ${CMAKE_SOURCE_DIR}/
  ${CMAKE_BINARY_DIR}
)

add_executable( properties properties.cpp )
target_link_libraries( properties fires )

add_executable( searchScalar searchScalar.cpp )
target_link_libraries( searchScalar fires )

add_executable( searchVector searchVector.cpp)
target_link_libraries( searchVector fires)

add_executable( searchLargeNumberOfObjects searchLargeNumberOfObjects.cpp)
target_link_libraries( searchLargeNumberOfObjects fires)

add_executable( filter filter.cpp )
target_link_libraries( filter fires )

add_executable( sort sort.cpp )
target_link_libraries( sort fires )

add_executable( aggregate aggregate.cpp )
target_link_libraries( aggregate fires )

add_executable( tasks tasks.cpp )
target_link_libraries( tasks fires )


# add_executable(floatPropertiesNormalization
# floatPropertysNormalization.cpp)
# target_link_libraries(floatPropertiessNormalization fires)
