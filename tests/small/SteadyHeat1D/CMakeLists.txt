# The root name for the tests in this directory is the directory name
get_filename_component(testName ${CMAKE_CURRENT_SOURCE_DIR} NAME)

if (ALBANY_EPETRA) 
  # Copy Input file from source to binary dir
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input.yaml COPYONLY)
  # Create the test with this name and standard executable
  AlbanyCreateTest (${testName}_Epetra input.yaml
    LABELS "Basic;Epetra;Forward"
  )

  # Additional files for restart testing
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_restart.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_restart.yaml COPYONLY)

  AlbanyCreateTest (${testName}_restart input_restart.yaml
    LABELS "Basic;Epetra;Forward"
    DEPENDS  ${testName}_Epetra
  )
endif()

if (ALBANY_IFPACK2)
  # Copy Input file from source to binary dir
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/inputT.yaml COPYONLY)
  # Create the test with this name and standard executable
  AlbanyCreateTest (${testName}_Tpetra inputT.yaml
    LABELS "Basic;Tpetra;Forward"
  )
endif ()
