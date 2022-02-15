# Name the test with the directory name
get_filename_component(testNameRoot ${CMAKE_CURRENT_SOURCE_DIR} NAME)

####################################
###        FO dome tests         ###
####################################

if(ALBANY_SEACAS)
  set(testName ${testNameRoot}_Dome)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_dome.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_dome.yaml COPYONLY)

  AlbanyCreateTest (${testName}_SDBC input_fo_dome.yaml
    LABELS "LandIce;Tpetra;Forward"
  )

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_domeAnalysis.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_domeAnalysis.yaml COPYONLY)

  AlbanyCreateTest (${testName}_Analysis input_fo_dome.yaml
    LABELS "LandIce;Tpetra;Forward"
  )

  if (ALBANY_EPETRA) 
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_dome_interpSurf.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input_fo_dome_interpSurf.yaml COPYONLY)

    AlbanyCreateTest (${testName}_interpSurf input_fo_dome_interpSurf.yaml
      LABELS "LandIce;Epetra;Forward"
    )
  endif()
endif()

####################################
###     Confined Shelf tets      ###
####################################

set(testName ${testNameRoot}_ConfinedShelf)
if (ALBANY_EPETRA)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_confinedShelf.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_confinedShelf.yaml COPYONLY)

  AlbanyCreateTest (${testName}_Epetra input_fo_confinedShelf.yaml
    LABELS "LandIce;Epetra;Forward"
  )
endif()

if (ALBANY_ifPACK2) 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_confinedShelfT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_confinedShelfT.yaml COPYONLY)

  AlbanyCreateTest (${testName}_Tpetra input_fo_confinedShelfT.yaml
    LABELS "LandIce;Tpetra;Forward"
  )
endif()

set(testName ${testNameRoot}_ConfinedShelf_DepthIntBC)
if (ALBANY_EPETRA)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_confinedShelf_depthIntBC.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_confinedShelf_depthIntBC.yaml COPYONLY)

  AlbanyCreateTest (${testName}_Epetra input_fo_confinedShelf_depthIntBC.yaml
    LABELS "LandIce;Epetra;Forward"
  )
endif()

if (ALBANY_ifPACK2) 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_confinedShelf_depthIntBCT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_confinedShelf_depthIntBCT.yaml COPYONLY)

  AlbanyCreateTest (${testName}_Tpetra input_fo_confinedShelf_depthIntBCT.yaml
    LABELS "LandIce;Tpetra;Forward"
  )
endif()

####################################
###     Circular Shelf tets      ###
####################################

if(ALBANY_SEACAS)
  set (testName ${testNameRoot}_CircularShelf)
  if (ALBANY_EPETRA) 
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_circularShelf.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input_fo_circularShelf.yaml COPYONLY)

    AlbanyCreateTest (${testName}_Epetra input_fo_circularShelf.yaml
      LABELS "LandIce;Epetra;Forward"
    )
  endif()

  if (ALBANY_ifPACK2) 
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_circularShelfT.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input_fo_circularShelfT.yaml COPYONLY)

    AlbanyCreateTest (${testName}_Tpetra input_fo_circularShelfT.yaml
      LABELS "LandIce;Tpetra;Forward"
    )
  endif()
endif()
