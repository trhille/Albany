# Name the test with the directory name
get_filename_component(testNameRoot ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Copy mesh files from source to binary dir
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/quadQuad.exo
               ${CMAKE_CURRENT_BINARY_DIR}/quadQuad.exo COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/quadQuad.exo.4.0
               ${CMAKE_CURRENT_BINARY_DIR}/quadQuad.exo.4.0 COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/quadQuad.exo.4.1
               ${CMAKE_CURRENT_BINARY_DIR}/quadQuad.exo.4.1 COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/quadQuad.exo.4.2
               ${CMAKE_CURRENT_BINARY_DIR}/quadQuad.exo.4.2 COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/quadQuad.exo.4.3
               ${CMAKE_CURRENT_BINARY_DIR}/quadQuad.exo.4.3 COPYONLY)

####################################
###     Parallel input tests     ###
####################################

set(testName ${testNameRoot})

if (ALBANY_EPETRA) 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input.yaml COPYONLY)

  AlbanyCreateTest (${testName}_Epetra input.yaml
    LABELS "Basic;Epetra;Forward"
  )
endif()
if (ALBANY_IFPACK2)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/inputT.yaml COPYONLY)

  AlbanyCreateTest (${testName}_Tpetra inputT.yaml
    LABELS "Basic;Tpetra;Forward"
  )
endif()

####################################
###      Serial input tests      ###
####################################

if (ALBANY_PARALELL_EXODUS)
  set(testName ${testNameRoot}_SerialInput)
  if (ALBANY_EPETRA)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_Serial.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input_Serial.yaml COPYONLY)

    AlbanyCreateTest (${testName}_Epetra input_Serial.yaml
      LABELS "Basic;Epetra;Forward"
    )
  endif()

  if (ALBANY_IFPACK2)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputT_Serial.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/inputT_Serial.yaml COPYONLY)
    AlbanyCreateTest (${testName}_Tpetra inputT_Serial.yaml
      LABELS "Basic;Tpetra;Forward"
    )

  endif ()
endif ()
