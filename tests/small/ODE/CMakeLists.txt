IF (NOT ALBANY_PARALLEL_ONLY)
  # Name the test with the directory name
  get_filename_component(testNameRoot ${CMAKE_CURRENT_SOURCE_DIR}_SERIAL NAME)

  ####################################
  ###            Tests             ###
  ####################################

  set(testName ${testNameRoot}_no_prec)
  IF(ALBANY_EPETRA)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input.yaml COPYONLY)

    AlbanyCreateTest (${testName}_Epetra input.yaml
      SERIAL LABELS "Demo;Epetra;Forward;Serial"
    )
  ENDIF()

  # if (NOT (ALBANY_CHECK_FPE OR ALBANY_STRONG_FPE_CHECK))
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputT.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/inputT.yaml COPYONLY)
    # Fails with FPE if FPE checking is enabled
    AlbanyCreateTest (${testName}_Tpetra inputT.yaml
      SERIAL LABELS "Demo;Tpetra;Forward;Serial"
    )
  # endif ()

  set(testName ${testNameRoot}_Ifpack2)
  if (ALBANY_IFPACK2)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputTP.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/inputTP.yaml COPYONLY)

    AlbanyCreateTest (${testName} inputTP.yaml
      SERIAL LABELS "Demo;Tpetra;Forward;Serial"
    )
  endif()
ENDIF()
