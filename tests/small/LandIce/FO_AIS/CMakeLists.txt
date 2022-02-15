get_filename_component(testNameRoot ${CMAKE_CURRENT_SOURCE_DIR}_16km NAME)

# This variable will be set in the input files during the 'configure_file' call
if (ALBANY_PARALELL_EXODUS)
  set (USE_SERIAL_MESH "true")
else ()
  # If there's no Iopx, we *must* have ALBANY_DECOMP defined (to decompose the mesh)
  # OR execute with only one rank.
  IF (ALBANY_MPI AND NOT ${ALBANY_SEACAS_PATH})
    MESSAGE (FATAL_ERROR "Error! Cannot execute FO_AIS tests in parallel without Iopx or decomp from Trilinos.\n")
  ENDIF()
  set (USE_SERIAL_MESH "false")
endif()

# Copy mesh and input files from source dir to binary dir
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/antarctica_2d.exo
               ${CMAKE_CURRENT_BINARY_DIR}/antarctica_2d.exo COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/surface_height.ascii
               ${CMAKE_CURRENT_BINARY_DIR}/surface_height.ascii COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/thickness.ascii
               ${CMAKE_CURRENT_BINARY_DIR}/thickness.ascii COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/temperature.ascii
               ${CMAKE_CURRENT_BINARY_DIR}/temperature.ascii COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/basal_friction_reg.ascii
               ${CMAKE_CURRENT_BINARY_DIR}/basal_friction_reg.ascii COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/surface_velocity.ascii
               ${CMAKE_CURRENT_BINARY_DIR}/surface_velocity.ascii COPYONLY)
                 
if (NOT ALBANY_PARALELL_EXODUS AND ALBANY_MPI)
  add_test (NAME FO_AIS_decompMesh
        COMMAND ${SEACAS_DECOMP} -processors ${MPIMNP} antarctica_2d.exo
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  set_tests_properties (FO_AIS_decompMesh PROPERTIES FIXTURES_SETUP antarcticaMeshSetup)
  set (decompMesh TRUE)
endif()


if (ALBANY_EPETRA) 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputML.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/inputML.yaml)
  AlbanyCreateTest (${testNameRoot}_ML inputML.yaml
    NP8
    LABELS "LandIce;Epetra;Forward"
    FIXTURES_REQUIRED_IF decompMesh antarcticaMeshSetup
  )
endif()

if(ALBANY_MUELU)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputMueLuShort.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/inputMueLuShort.yaml)
  AlbanyCreateTest (${testNameRoot}_MueLuShortList inputMueLuShort.yaml
    NP8
    LABELS "LandIce;Tpetra;Forward"
    FIXTURES_REQUIRED_IF decompMesh antarcticaMeshSetup
  )

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inputMueLu.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/inputMueLu.yaml)
  AlbanyCreateTest (${testNameRoot}_MueLu inputMueLu.yaml
    NP8
    LABELS "LandIce;Tpetra;Forward"
    FIXTURES_REQUIRED_IF decompMesh antarcticaMeshSetup
  )
endif()

# if (ALBANY_FROSCH)
#   configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_FROSch.yaml
#                  ${CMAKE_CURRENT_BINARY_DIR}/input_FROSch.yaml)
#   AlbanyCreateTest (${testNameRoot}_FROSch input_FROSch.yaml
#     LABELS "LandIce;Tpetra;Forward"
#     FIXTURES_REQUIRED_IF decompMesh antarcticaMeshSetup)
#   )
# endif()=
