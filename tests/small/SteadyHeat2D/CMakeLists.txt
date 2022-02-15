# The root name for the tests in this directory is the directory name
get_filename_component(testNameRoot ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Create the test with this name and standard executable
set(testName ${testNameRoot})
if (ALBANY_EPETRA) 

  # Copy Input file from source to binary dir
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input.yaml COPYONLY)
  AlbanyCreateTest (${testName}_Epetra input.yaml
    LABELS "Basic;Epetra;Forward"
  )
endif()

if (ALBANY_IFPACK2)
  # Copy Input file from source to binary dir
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/inputT.yaml COPYONLY)

  AlbanyCreateTest (${testName}_Tpetra inputT.yaml
    LABELS "Basic;Tpetra;Forward"
  )

  AlbanyCreateTest (${testName}_SERIAL inputT.yaml
    SERIAL LABELS "Basic;Tpetra;Forward"
  )

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputT_RegressFail.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/inputT_RegressFail.yaml COPYONLY)
  AlbanyCreateTest (${testName}_RegressFail inputT_RegressFail.yaml
    SERIAL WILL_FAIL LABELS "Basic;Tpetra;Forward;RegressFail"
  )
endif ()

if (ALBANY_MUELU_EXAMPLES)
  set (testName ${testNameRoot}_MueLu)

  # Copy Input file from source to binary dir
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputT_MueLu.yaml
             ${CMAKE_CURRENT_BINARY_DIR}/inputT_MueLu.yaml COPYONLY)
  # Create the tests with this name and standard executable
  AlbanyCreateTest (${testName} inputT_MueLu.yaml
    LABELS "Basic;Tpetra;Forward"
  )

  AlbanyCreateTest (${testName}_SERIAL inputT_MueLu.yaml
    SERIAL LABELS "Basic;Tpetra;Forward"
  )

  # Regress fail test
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputT_MueLu_RegressFail.yaml
             ${CMAKE_CURRENT_BINARY_DIR}/inputT_MueLu_RegressFail.yaml COPYONLY)
  AlbanyCreateTest (${testName}_RegressFail inputT_MueLu_RegressFail.yaml
    SERIAL WILL_FAIL LABELS "Basic;Tpetra;Forward;RegressFail"
  )
endif ()
