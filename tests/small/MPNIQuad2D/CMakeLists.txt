# Name the test with the directory name
get_filename_component(testNameRoot ${CMAKE_CURRENT_SOURCE_DIR} NAME)

####################################
###          Main tests          ###
####################################

set(testName ${testNameRoot})

if (ALBANY_EPETRA AND ALBANY_STOKHOS) 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input.yaml COPYONLY)

  AlbanyCreateTest (${testName}_Epetra input.yaml
    LABELS "Stokhos;Epetra;Forward"
  )
endif()

if (ALBANY_MUELU AND ALBANY_STOKHOS)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/inputT.yaml COPYONLY)

  AlbanyCreateTest (${testName}_Tpetra inputT.yaml
    LABELS "Stokhos;Tpetra;Forward"
  )
endif ()
