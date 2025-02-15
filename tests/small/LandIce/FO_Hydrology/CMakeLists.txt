# Name the test with the directory name
get_filename_component(testNameRoot ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# This variable will be set in the input files during the 'configure_file' call
if (ALBANY_PARALELL_EXODUS)
  set (USE_SERIAL_MESH "true")
#IKT 5/22/19 - commenting out for now as this is leading to compilation error
else ()
  # If there's no Iopx, we *must* have ALBANY_DECOMP defined (to decompose the mesh)
  # OR execute with only one rank.
  IF (ALBANY_MPI AND NOT ${ALBANY_SEACAS_PATH})
    MESSAGE (FATAL_ERROR "Error! Cannot execute FO_GIS tests in parallel without Iopx or decomp from Trilinos.\n")
  ENDIF()
 set (USE_SERIAL_MESH "false")
endif()

####################################
###           Dome Test          ###
####################################

set (testName ${testNameRoot}_Steady)

if (ALBANY_IFPACK2)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_dome_steady_fwd.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_dome_steady_fwd.yaml)
  add_test(${testName}_Dome_Tpetra ${Albany.exe}  input_dome_steady_fwd.yaml)
  set_tests_properties(${testName}_Dome_Tpetra
                       PROPERTIES
                       LABELS "LandIce;Tpetra;Forward")
endif()
