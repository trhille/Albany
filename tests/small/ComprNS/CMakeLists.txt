if (ALBANY_EPETRA) 
  # Name the test with the directory name
  get_filename_component(testName ${CMAKE_CURRENT_SOURCE_DIR}_2DTaylorGreenVortex_SDBC  NAME)

  # Create the test with this name and standard executable
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input2D_taylorGreenVortex.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input2D_taylorGreenVortex.yaml COPYONLY)

  AlbanyCreateTest (${testName} input2D_taylorGreenVortex.yaml
    LABELS "Demo;Epetra;Forward"
  )
endif()

