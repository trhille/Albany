get_filename_component(testName ${CMAKE_CURRENT_SOURCE_DIR}  NAME)
if (ALBANY_EPETRA) 

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_ismip-hom_testA.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_ismip-hom_testA.yaml COPYONLY)

  AlbanyCreateTest (${testName}_TestA input_ismip-hom_testA.yaml
    LABELS "LandIce;Epetra;Forward"
  )
endif()
