if(FIRES_WITH_EXAMPLES)

  # Function to create and install an example application
  function(add_project_example)
    set(options)
    set(oneValueArgs TARGET_NAME)
    set(multiValueArgs SOURCES LINK_LIBRARIES)
    cmake_parse_arguments(PARSE_ARGV 0 ARG "${options}" "${oneValueArgs}" "${multiValueArgs}")

    if(NOT ARG_TARGET_NAME OR NOT ARG_SOURCES)
      message(FATAL_ERROR "TARGET_NAME and SOURCES are required arguments")
    endif()

    add_executable(${ARG_TARGET_NAME} ${ARG_SOURCES})
    target_link_libraries(${ARG_TARGET_NAME} PRIVATE ${PROJECT_NAME} ${ARG_LINK_LIBRARIES})

    # Get current parent scope value and create a local copy
    set(PROJECT_EXAMPLES_FILES_VAR "${${PROJECT_NAME}_EXAMPLES_FILES}")
    set(current_examples ${PROJECT_EXAMPLES_FILES_VAR})
    
    # Convert to CMake list and append new sources
    list(APPEND current_examples ${ARG_SOURCES})
    
    # Remove duplicates and update parent scope
    list(REMOVE_DUPLICATES current_examples)
    set(${PROJECT_NAME}_EXAMPLES_FILES "${current_examples}" PARENT_SCOPE)

    # Create all examples target
    if(NOT TARGET ${PROJECT_NAME}_all_examples)
      add_custom_target(${PROJECT_NAME}_all_examples)
    endif()

    # Add example to global examples target
    add_dependencies(${PROJECT_NAME}_all_examples ${ARG_TARGET_NAME})
  endfunction()

  # Add examples
  add_project_example(
    TARGET_NAME firesExampleAggregate
    SOURCES
      aggregate.cpp
  )

  add_project_example(
    TARGET_NAME firesExampleCaster
    SOURCES
      caster.cpp
  )

  add_project_example(
    TARGET_NAME firesExampleDependencies
    SOURCES
      dependencies.cpp
  )

  add_project_example(
    TARGET_NAME firesExampleFilter
    SOURCES
      filter.cpp
  )

  # add_project_example(
  #   TARGET_NAME firesExampleFloatFeaturesNormalization
  #   SOURCES
  #     floatFeaturesNormalization.cpp
  # )

  add_project_example(
    TARGET_NAME firesExampleObserver
    SOURCES
      observer.cpp
  )

  add_project_example(
    TARGET_NAME firesExampleProperties
    SOURCES
      properties.cpp
  )

  add_project_example(
    TARGET_NAME firesExampleSearchLargeNumberOfObjects
    SOURCES
      searchLargeNumberOfObjects.cpp
  )

  add_project_example(
    TARGET_NAME firesExampleSearchScalar
    SOURCES
      searchScalar.cpp
  )

  add_project_example(
    TARGET_NAME firesExampleSerialize
    SOURCES
      serialize.cpp
  )

  add_project_example(
    TARGET_NAME firesExampleSort
    SOURCES
      sort.cpp
  )

  add_project_example(
    TARGET_NAME firesExampleTask
    SOURCES
      tasks.cpp
  )

  # Define installation directory variables
  include(GNUInstallDirs)

  # Install examples source files
  install(FILES ${${PROJECT_NAME}_EXAMPLES_FILES}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME_LOWER}/examples
    COMPONENT ${PROJECT_NAME}_examples
  )

endif()