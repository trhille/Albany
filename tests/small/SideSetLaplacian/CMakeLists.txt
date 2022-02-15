if (ALBANY_EPETRA) 
  # 1. Copy Input file from source to binary dir
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_2D.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_2D.yaml COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_3D.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_3D.yaml COPYONLY)
  get_filename_component(testName ${CMAKE_CURRENT_SOURCE_DIR} NAME)

  AlbanyCreateTest (${testName}_2D input_2D.yaml
    LABELS "Basic;Epetra;Forward"
  )

  AlbanyCreateTest (${testName}_3D input_3D.yaml
    LABELS "Basic;Epetra;Forward"
  )
endif()
