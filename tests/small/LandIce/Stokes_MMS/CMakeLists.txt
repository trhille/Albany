# Name the test with the directory name
get_filename_component(testNameRoot ${CMAKE_CURRENT_SOURCE_DIR} NAME)

####################################
###          Poly test           ###
####################################

set(testName ${testNameRoot}_Poly)

if (ALBANY_EPETRA) 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input.yaml COPYONLY)
  AlbanyCreateTest (${testName}_Epetra input.yaml
    LABELS "LandIce;Epetra;Forward"
  )
endif()

if (ALBANY_IFPACK2) 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/inputT.yaml COPYONLY)
  AlbanyCreateTest (${testName}_Tpetra inputT.yaml
    LABELS "LandIce;Tpetra;Forward"
  )
endif()

####################################
###     Couette Periodic test    ###
####################################

set(testName ${testNameRoot}_CouettePeriodicX)

if (ALBANY_EPETRA) 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_couette_periodic.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_couette_periodic.yaml COPYONLY)
  AlbanyCreateTest (${testName} input_couette_periodic.yaml
    LABELS "LandIce;Epetra;Forward"
  )
endif()

####################################
###    SinSin PeriodicXY test    ###
####################################

set(testName ${testNameRoot}_SinSinPeriodicXY)

if (ALBANY_EPETRA) 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_sinsin.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_sinsin.yaml COPYONLY)
  AlbanyCreateTest (${testName} input_sinsin.yaml
    LABELS "LandIce;Epetra;Forward"
  )
endif()

####################################
###     SinSin Dirichlet test    ###
####################################

set(testName ${testNameRoot}_SinSinDirichlet)

if (ALBANY_EPETRA) 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_sinsin_dirichlet.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_sinsin_dirichlet.yaml COPYONLY)
  AlbanyCreateTest (${testName} input_sinsin_dirichlet.yaml
    LABELS "LandIce;Epetra;Forward"
  )
endif()

####################################
###    SinCosZ Dirichlet test    ###
####################################

set(testName ${testNameRoot}_SinCosZ3DDirichlet)

if (ALBANY_EPETRA) 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_sincosz_dirichlet.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_sincosz_dirichlet.yaml COPYONLY)
  AlbanyCreateTest (${testName} input_sincosz_dirichlet.yaml
    LABELS "LandIce;Epetra;Forward"
  )
endif()

####################################
###    SinCosZ Periodic test     ###
####################################

set(testName ${testNameRoot}_SinCosZ3DPeriodicXY)

if (ALBANY_EPETRA) 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_sincosz.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_sincosz.yaml COPYONLY)
  AlbanyCreateTest (${testName} input_sincosz.yaml
    LABELS "LandIce;Epetra;Forward"
  )
endif()

####################################
###       SinCos Glen test       ###
####################################

set(testName ${testNameRoot}_SinCosGlen)

if (ALBANY_EPETRA) 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_sincos_glen.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_sincos_glen.yaml COPYONLY)
  AlbanyCreateTest (${testName} input_sincos_glen.yaml
    LABELS "LandIce;Epetra;Forward"
  )
endif()

####################################
###      SinExp Basal test       ###
####################################

set(testName ${testNameRoot}_SinExpBasal)

if (ALBANY_EPETRA) 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_sinexp_basal.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_sinexp_basal.yaml COPYONLY)
  AlbanyCreateTest (${testName} input_sinexp_basal.yaml
    LABELS "LandIce;Epetra;Forward"
  )
endif()
