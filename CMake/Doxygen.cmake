
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
