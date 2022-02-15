IF(NOT ALBANY_PARALLEL_ONLY)
  # Name the test with the directory name
  get_filename_component(testName ${CMAKE_CURRENT_SOURCE_DIR}_SERIAL NAME)

  # Copy mesh file from source dir to binary dir
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cube.exo
                 ${CMAKE_CURRENT_BINARY_DIR}/cube.exo COPYONLY)

  # Create the test with this name and standard executable
  if (ALBANY_EPETRA) 
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input.yaml COPYONLY)
    AlbanyCreateTest (${testName}_Epetra input.yaml
      SERIAL LABELS "Basic;Epetra;Forward"
    )
  endif()
  if (ALBANY_IFPACK2)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputT.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/inputT.yaml COPYONLY)
    AlbanyCreateTest (${testName}_Tpetra inputT.yaml
      SERIAL LABELS "Basic;Tpetra;Forward"
    )
  endif ()
ENDIF()
