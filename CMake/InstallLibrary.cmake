
foreach(ITEM ${DEPLOY_FILES_AND_DIRS})
   if( IS_DIRECTORY "${ITEM}" )
      list( APPEND DIRS_TO_DEPLOY "${ITEM}" )
   else()
     get_filename_component(FILE_EXT "${ITEM}" "EXT")
     if( FILE_EXT STREQUAL ".h")
       list( APPEND FILES_TO_DEPLOY "${ITEM}" )
     endif()
   endif()
endforeach()

# Install rules
install( FILES ${FILES_TO_DEPLOY} DESTINATION include/${PROJECT_NAME} )
install( FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/config.h 
  DESTINATION include/${PROJECT_NAME} )
install( DIRECTORY ${DIRS_TO_DEPLOY} DESTINATION include/${PROJECT_NAME} )
install(TARGETS ${PROJECT_NAME} 
  EXPORT ${PROJECT_NAME}Targets
  DESTINATION ${INSTALL_LIB_DIR}
  COMPONENT dev)
