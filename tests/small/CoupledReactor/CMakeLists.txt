if (ALBANY_EPETRA) 
  # Name the test with the directory name
  get_filename_component(testName ${CMAKE_CURRENT_SOURCE_DIR} NAME)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_domain_coupled.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_domain_coupled.yaml COPYONLY)

  # Create the test
  AlbanyCreateTest (${testName}_Epetra input_domain_coupled.yaml
    LABELS "Demo;Epetra;Forward"
  )
endif()

