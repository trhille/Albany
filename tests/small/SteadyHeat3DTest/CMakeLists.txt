if (ALBANY_EPETRA) 
  # Copy Input file from source to binary dir
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputA.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/inputA.yaml COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputB.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/inputB.yaml COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputC.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/inputC.yaml COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputD.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/inputD.yaml COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/beam.pg
                 ${CMAKE_CURRENT_BINARY_DIR}/beam.pg COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/materials.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/materials.yaml COPYONLY)

  # 2. Name the test with the directory name
  get_filename_component(testName ${CMAKE_CURRENT_SOURCE_DIR} NAME)

  AlbanyCreateTest (${testName}_A inputA.yaml
    LABELS "Basic;Epetra;Forward"
  )

  AlbanyCreateTest (${testName}_B inputB.yaml
    LABELS "Basic;Epetra;Forward"
  )

  AlbanyCreateTest (${testName}_C inputC.yaml
    LABELS "Basic;Epetra;Forward"
  )

  AlbanyCreateTest (${testName}_D inputD.yaml
    LABELS "Basic;Epetra;Forward"
  )
endif()
