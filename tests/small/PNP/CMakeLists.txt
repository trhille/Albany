# Name the test with the directory name
get_filename_component(testName ${CMAKE_CURRENT_SOURCE_DIR}_test2D NAME)

if (ALBANY_EPETRA) 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_test2D.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_test2D.yaml COPYONLY)

  AlbanyCreateTest (${testName}_Epetra input_test2D.yaml
    LABELS "Demo;Epetra;Forward"
  )
endif()

if (ALBANY_IFPACK2)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_test2DT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_test2DT.yaml COPYONLY)

  AlbanyCreateTest (${testName}_Tpetra input_test2DT.yaml
    LABELS "Demo;Tpetra;Forward"
  )
endif ()
