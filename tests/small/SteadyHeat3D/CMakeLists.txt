# The root name for the tests in this directory is the directory name
get_filename_component(testNameRoot ${CMAKE_CURRENT_SOURCE_DIR} NAME)

####################################
###          Main tests          ###
####################################

if (ALBANY_EPETRA) 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input.yaml COPYONLY)

  AlbanyCreateTest (${testNameRoot}_Epetra input.yaml
    LABELS "Basic;Epetra;Forward"
  )
endif()

if (ALBANY_IFPACK2)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/inputT.yaml COPYONLY)

  AlbanyCreateTest (${testNameRoot}_Tpetra inputT.yaml
    LABELS "Basic;Tpetra;Forward"
  )
endif ()

####################################
###         Ascii tests          ###
####################################

IF (NOT ALBANY_PARALLEL_ONLY)
  set(testName ${testNameRoot}_10x10x10_ascii)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/xyz
                 ${CMAKE_CURRENT_BINARY_DIR}/xyz COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/eles
                 ${CMAKE_CURRENT_BINARY_DIR}/eles COPYONLY)

  IF(ALBANY_EPETRA)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_10x10x10_ascii.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input_10x10x10_ascii.yaml COPYONLY)

    AlbanyCreateTest (${testName}_Epetra input_10x10x10_ascii.yaml
      SERIAL LABELS "Basic;Epetra;Forward"
    )
  ENDIF()

  if (ALBANY_IFPACK2)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputT_10x10x10_ascii.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/inputT_10x10x10_ascii.yaml COPYONLY)

    AlbanyCreateTest (${testName}_Tpetra inputT_10x10x10_ascii.yaml
      SERIAL LABELS "Basic;Tpetra;Forward"
    )
  endif ()
ENDIF ()

####################################
###     Node GID Array tests     ###
####################################

set(testName ${testNameRoot}_nodeGIDArrayResponse)

if (ALBANY_EPETRA) 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_nodeGIDArrayResponse.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_nodeGIDArrayResponse.yaml COPYONLY)

  AlbanyCreateTest (${testName}_Epetra input_nodeGIDArrayResponse.yaml
    LABELS "Basic;Epetra;Forward"
  )
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputT_nodeGIDArrayResponse.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/inputT_nodeGIDArrayResponse.yaml COPYONLY)

AlbanyCreateTest (${testName}_Tpetra inputT_nodeGIDArrayResponse.yaml
  LABELS "Basic;Tpetra;Forward"
)
