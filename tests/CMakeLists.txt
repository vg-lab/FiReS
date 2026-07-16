if(FIRES_WITH_TESTS)

  # Function to add a test
  function(add_project_test NAME SOURCE)
    add_executable(${NAME} ${SOURCE})
    target_include_directories(${NAME}
      PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
    )
    target_link_libraries(${NAME} PRIVATE
      ${PROJECT_NAME}
      Boost::unit_test_framework
    )
    add_test(NAME ${NAME} COMMAND ${NAME})

    # Create all tests target
    if(NOT TARGET ${PROJECT_NAME}_all_tests)
      add_custom_target(${PROJECT_NAME}_all_tests)
    endif()

    # Add test to global tests target
    add_dependencies(${PROJECT_NAME}_all_tests ${NAME})
  endfunction()

  # Add tests
  add_project_test(firesTestAverager Averager.cpp)
  add_project_test(firesTestComparer Comparer.cpp)
  add_project_test(firesTestDependencies Dependencies.cpp)
  add_project_test(firesTestFilter Filter.cpp)
  add_project_test(firesTestObject Object.cpp)
  add_project_test(firesTestProperty Property.cpp)
  add_project_test(firesTestPropertyCaster PropertyCaster.cpp)
  add_project_test(firesTestPropertyGIDManger PropertyGIDManager.cpp)

endif()