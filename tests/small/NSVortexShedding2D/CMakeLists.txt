# Name the test with the directory name
get_filename_component(testNameRoot ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Copy mesh files from source to binary dir
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vortex.exo
               ${CMAKE_CURRENT_BINARY_DIR}/vortex.exo COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vortex.exo.4.0
               ${CMAKE_CURRENT_BINARY_DIR}/vortex.exo.4.0 COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vortex.exo.4.1
               ${CMAKE_CURRENT_BINARY_DIR}/vortex.exo.4.1 COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vortex.exo.4.2
               ${CMAKE_CURRENT_BINARY_DIR}/vortex.exo.4.2 COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vortex.exo.4.3
               ${CMAKE_CURRENT_BINARY_DIR}/vortex.exo.4.3 COPYONLY)

####################################
###         Steady tests         ###
####################################

if (ALBANY_EPETRA)
  set (testName ${testNameRoot}_Steady)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input.yaml COPYONLY)

  AlbanyCreateTest (${testName} input.yaml
    LABELS "Demo;Epetra;Forward"
  )

# This block test looks at Epetra and separate the physics variables into blocks
# but keep them in the same solution vector (the usual monolithic solve in the stack)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputBlockedMono.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/inputBlockedMono.yaml COPYONLY)

  AlbanyCreateTest (${testName}_Blocked inputBlockedMono.yaml
    LABELS "Demo;Epetra;Forward"
  )

endif()

# We demo two blocked tests in this section

# This block test looks at Tpetra and Thyra_ProductVector to block the physics variables and
# separate the blocks throughout the software stack

set (testName ${testNameRoot})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputBlockedSolv.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/inputBlockedSolv.yaml COPYONLY)

# Comment until we get it working
#AlbanyCreateTest (${testName}_BlockedSolv inputBlockedSolv.yaml
# LABELS "Demo;Tpetra;Forward"
#)

####################################
###       Transient tests        ###
####################################

set (testName ${testNameRoot}_TransientIRK)

if (ALBANY_EPETRA)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputTransientRK.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/inputTransientRK.yaml COPYONLY)

  AlbanyCreateTest (${testName}_Epetra inputTransientRK.yaml
    LABELS "Demo;Epetra;Forward"
  )
endif(ALBANY_EPETRA)

if (ALBANY_IFPACK2)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputTransientRKT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/inputTransientRKT.yaml COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputTransientRKT_RegressFail.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/inputTransientRKT_RegressFail.yaml COPYONLY)

  AlbanyCreateTest (${testName}_Tpetra inputTransientRKT.yaml
    LABELS "Demo;Tpetra;Forward"
  )

  AlbanyCreateTest (${testName}_Tpetra_RegressFail inputTransientRKT_RegressFail.yaml
    WILL_FAIL LABELS "Demo;Tpetra;Forward;RegressFail"
  )
endif(ALBANY_IFPACK2)
