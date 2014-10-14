

include_directories(${CMAKE_BINARY_DIR})

enable_testing()

find_library(GTEST_LIBRARY 
 NAMES libgtest.a
 PATHS 
 ${GTEST_LIBRARY_DIR}
 /opt/local/lib
 /usr/local/lib
 /usr/lib
)

if (GTEST_LIBRARY)

  get_filename_component(
    GTEST_LIBRARY_DIR 
    ${GTEST_LIBRARY}
    PATH )

  message(STATUS "Found Gtest in ${GTEST_LIBRARY}")
  link_directories( ${GTEST_LIBRARY_DIR} )
  include_directories(${GTEST_INCLUDE_DIR})
  find_package (Threads)
  add_executable(runTests runTests.cpp )
  target_link_libraries(runTests gtest ${CMAKE_THREAD_LIBS_INIT} fires)
else()
  message(STATUS "Missing Gtest. No test will be built")
endif()
