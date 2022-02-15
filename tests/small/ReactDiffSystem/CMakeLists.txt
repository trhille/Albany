IF (ALBANY_IFPACK2)
  # Name the test with the directory name
  get_filename_component(testName ${CMAKE_CURRENT_SOURCE_DIR} NAME)

  # Copy Input file from source to binary dir
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/inputT.yaml COPYONLY)

  # Create the test with this name and standard executable
  AlbanyCreateTest (${testName} inputT.yaml
    LABELS "Demo;Tpetra;Forward"
  )
ENDIF()
