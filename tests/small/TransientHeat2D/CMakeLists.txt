# The root name for the tests in this directory is the directory name
get_filename_component(testNameRoot ${CMAKE_CURRENT_SOURCE_DIR} NAME)

#
# Tempus tests
#

# BE test
set(testName ${testNameRoot}_Tempus_BackwardEuler_NOXSolver)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tempus_be_nox_solver.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/tempus_be_nox_solver.yaml COPYONLY)

AlbanyCreateTest (${testName} tempus_be_nox_solver.yaml
  LABELS "Basic;Tempus;Tpetra;Forward"
)

# RK 4 test
#set(testName ${testNameRoot}_Tempus_GERK)
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tempus_gerk.yaml
#               ${CMAKE_CURRENT_BINARY_DIR}/tempus_gerk.yaml COPYONLY)

#AlbanyCreateTest (${testName} tempus_gerk.yaml
#  LABELS "Basic;Tempus;Tpetra;Forward"
#)
