# Name the test with the directory name
get_filename_component(testNameRoot ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Copy mesh files from source to binary dir
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/quadOut.exo
               ${CMAKE_CURRENT_BINARY_DIR}/quadOut.exo COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/quadOut.exo.4.0
               ${CMAKE_CURRENT_BINARY_DIR}/quadOut.exo.4.0 COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/quadOut.exo.4.1
               ${CMAKE_CURRENT_BINARY_DIR}/quadOut.exo.4.1 COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/quadOut.exo.4.2
               ${CMAKE_CURRENT_BINARY_DIR}/quadOut.exo.4.2 COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/quadOut.exo.4.3
               ${CMAKE_CURRENT_BINARY_DIR}/quadOut.exo.4.3 COPYONLY)

####################################
###          Main tests          ###
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
endif ()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputEnrich.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/inputEnrich.yaml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputConvert.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/inputConvert.yaml COPYONLY)

####################################
###        Refine tests          ###
####################################

IF(ALBANY_STK_PERCEPT)
  set (testName ${testNameRoot}_Refine)
  if (ALBANY_EPETRA) 
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputRefine1.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/inputRefine1.yaml COPYONLY)

    AlbanyCreateTest (${testName}_1_Epetra inputRefine1.yaml
      LABELS "Basic;Epetra;Forward"
    )

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputRefine2.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/inputRefine2.yaml COPYONLY)

    AlbanyCreateTest (${testName}_2_Epetra inputRefine2.yaml
      LABELS "Basic;Epetra;Forward"
    )

    # Enrich and convert both still have bugs
    #AlbanyCreateTest (${testName}_Enrich inputEnrich.yaml)
    #AlbanyCreateTest (${testName}_Convert inputConvert.yaml)
  endif()
ENDIF()
