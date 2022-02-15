get_filename_component(testName ${CMAKE_CURRENT_SOURCE_DIR} NAME)
if (ALBANY_EPETRA) 

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_dome.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_dome.yaml COPYONLY)

  AlbanyCreateTest (${testName}_Dome input_dome.yaml
    LABELS "LandIce;Epetra;Forward"
  )
endif()

