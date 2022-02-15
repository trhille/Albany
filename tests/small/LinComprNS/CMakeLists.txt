# Name the test with the directory name
get_filename_component(testNameRoot ${CMAKE_CURRENT_SOURCE_DIR} NAME)

####################################
###    1D Standing Wave test     ###
####################################

IF(NOT ALBANY_PARALLEL_ONLY AND ALBANY_EPETRA)
  set(testName ${testNameRoot}_1D_standingWave)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input1D_standingWave.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input1D_standingWave.yaml COPYONLY)

  AlbanyCreateTest (${testName} input1D_standingWave.yaml
    SERIAL LABELS "Demo;Epetra;Forward;Serial"
  )
endif()

####################################
###       2D Steady test         ###
####################################

IF(NOT ALBANY_PARALLEL_ONLY AND ALBANY_EPETRA)
  set(testName ${testNameRoot}_2DSteady)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input2D.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input2D.yaml COPYONLY)

  AlbanyCreateTest (${testName} input2D.yaml
    LABELS "Demo;Epetra;Forward;Serial"
  )
endif()

####################################
###      2D Press Pulse test     ###
####################################

if (ALBANY_IFPACK2)
  set(testName ${testNameRoot}_2DUnsteadyInvPressPulse)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input2Dunsteady.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input2Dunsteady.yaml COPYONLY)

  AlbanyCreateTest (${testName} input2Dunsteady.yaml
    LABELS "Demo;Tpetra;Forward"
  )
endif()

####################################
###      2D Euler MMS test       ###
####################################

IF(NOT ALBANY_PARALLEL_ONLY AND ALBANY_EPETRA)
  set(testName ${testNameRoot}_2DUnsteadyEulerMMS)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input2DunsteadyMMS.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input2DunsteadyMMS.yaml COPYONLY)
  AlbanyCreateTest (${testName} input2DunsteadyMMS.yaml
    SERIAL LABELS "Demo;Epetra;Forward;Serial"
  )
ENDIF()

####################################
###     2D Driven Pulse test     ###
####################################

IF(NOT ALBANY_PARALLEL_ONLY AND ALBANY_EPETRA)
  set(testName ${testNameRoot}_2DDrivenPulse)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input2D_drivenPulse.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input2D_drivenPulse.yaml COPYONLY)

  AlbanyCreateTest (${testName} input2D_drivenPulse.yaml
    SERIAL LABELS "Demo;Epetra;Forward;Serial"
  )
ENDIF()

####################################
###    3D Unsteady Euler test    ###
####################################

IF(NOT ALBANY_PARALLEL_ONLY AND ALBANY_EPETRA)
  set(testName ${testNameRoot}_3DUnsteadyEuler)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input3Dunsteady.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input3Dunsteady.yaml COPYONLY)

  AlbanyCreateTest (${testName} input3Dunsteady.yaml
    SERIAL LABELS "Demo;Epetra;Forward;Serial"
  )
ENDIF()

####################################
###      3D Unsteady NS test     ###
####################################

#IF(NOT ALBANY_PARALLEL_ONLY AND ALBANY_EPETRA)
#  set(testName ${testNameRoot}_3DUnsteadyNS)

#  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input3DunsteadyNS.yaml
#                 ${CMAKE_CURRENT_BINARY_DIR}/input3DunsteadyNS.yaml COPYONLY)

#  AlbanyCreateTest (${testName} input3DunsteadyNS.yaml
#    SERIAL LABELS "Demo;Epetra;Forward;Serial")
#ENDIF()
