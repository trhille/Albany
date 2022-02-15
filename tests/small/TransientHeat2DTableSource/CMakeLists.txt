if (ALBANY_EPETRA) 
  # Copy Input file from source to binary dir
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input.yaml COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputTrans.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/inputTrans.yaml COPYONLY)
  # Copy materials file from source to binary dir
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/materials.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/materials.yaml COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/qdot.dat
                 ${CMAKE_CURRENT_BINARY_DIR}/qdot.dat COPYONLY)

  # Copy mesh files from source to binary dir
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ebs.exo
                 ${CMAKE_CURRENT_BINARY_DIR}/ebs.exo COPYONLY)

  # Name the test with the directory name
  get_filename_component(testName ${CMAKE_CURRENT_SOURCE_DIR} NAME)

  # Create the tests

  AlbanyCreateTest (${testName}_Steady input.yaml
    SERIAL LABELS "Basic;Epetra;Forward;Serial"
  )

  AlbanyCreateTest (${testName}_Transient inputTrans.yaml
    SERIAL DEPENDS ${testName}_Steady
    LABELS "Basic;Epetra;Forward;Serial"
  )
endif()
