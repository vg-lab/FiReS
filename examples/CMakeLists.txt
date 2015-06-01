# Include directories
include_directories(
  ${CMAKE_SOURCE_DIR}/
  ${CMAKE_BINARY_DIR}
)

add_executable( scalarFeatures scalarFeatures.cpp )
target_link_libraries( scalarFeatures fires )

add_executable(vectorFeatures vectorFeatures.cpp)
target_link_libraries(vectorFeatures fires)

add_executable(floatFeaturesNormalization
floatFeaturesNormalization.cpp)
target_link_libraries(floatFeaturesNormalization fires)

add_executable(largeNumberOfObjects
largeNumberOfObjects.cpp)
target_link_libraries(largeNumberOfObjects fires)
