get_filename_component (testName ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# These tests require to set some input fields via a math expression.
# If PanzerExprEval is not found in Trilinos, we can't run them.
if (ALBANY_PANZER_EXPR_EVAL)

  # -------------------------------------- #
  #  Ed Bueler's quasi-analytic test case  #
  # -------------------------------------- #
  configure_file (${CMAKE_CURRENT_SOURCE_DIR}/input_bueler_steady.yaml
                  ${CMAKE_CURRENT_BINARY_DIR}/input_bueler_steady.yaml COPYONLY)
  configure_file (${CMAKE_CURRENT_SOURCE_DIR}/circle.msh
                  ${CMAKE_CURRENT_BINARY_DIR}/circle.msh COPYONLY)
  AlbanyCreateTest (${testName}_bueler_steady input_bueler_steady.yaml
    LABELS "LandIce;Tpetra;Forward"
  )

  # NOTE: the unsteady test produce a different solution than the steady one.
  #       It appears it takes *a lot of simulated years* for the unsteady solution
  #       to approach the steady one. And even after million of years, it seems that
  #       the water thickness is smoother and larger, compared to the SS case.
  #       This might be due to dissipation/dispersion induced by the time integrators.
  configure_file (${CMAKE_CURRENT_SOURCE_DIR}/input_bueler_unsteady.yaml
                  ${CMAKE_CURRENT_BINARY_DIR}/input_bueler_unsteady.yaml COPYONLY)
  AlbanyCreateTest (${testName}_bueler_unsteady input_bueler_unsteady.yaml
    LABELS "LandIce;Tpetra;Forward"
  )

  # -------------------------------------- #
  #            SHMIP suite A               #
  # -------------------------------------- #
  configure_file (${CMAKE_CURRENT_SOURCE_DIR}/input_suite_A1.yaml
                  ${CMAKE_CURRENT_BINARY_DIR}/input_suite_A1.yaml COPYONLY)
  AlbanyCreateTest (${testName}_suite_A1 input_suite_A1.yaml
    LABELS "LandIce;Tpetra;Forward"
  )

  configure_file (${CMAKE_CURRENT_SOURCE_DIR}/input_suite_A2.yaml
                  ${CMAKE_CURRENT_BINARY_DIR}/input_suite_A2.yaml COPYONLY)
  AlbanyCreateTest (${testName}_suite_A2 input_suite_A2.yaml
    LABELS "LandIce;Tpetra;Forward"
  )

  configure_file (${CMAKE_CURRENT_SOURCE_DIR}/input_suite_A3.yaml
                  ${CMAKE_CURRENT_BINARY_DIR}/input_suite_A3.yaml COPYONLY)
  AlbanyCreateTest (${testName}_suite_A3 input_suite_A3.yaml
    LABELS "LandIce;Tpetra;Forward"
  )

  configure_file (${CMAKE_CURRENT_SOURCE_DIR}/input_suite_A4.yaml
                  ${CMAKE_CURRENT_BINARY_DIR}/input_suite_A4.yaml COPYONLY)
  AlbanyCreateTest (${testName}_suite_A4 input_suite_A4.yaml
    LABELS "LandIce;Tpetra;Forward"
  )

  configure_file (${CMAKE_CURRENT_SOURCE_DIR}/input_suite_A5.yaml
                  ${CMAKE_CURRENT_BINARY_DIR}/input_suite_A5.yaml COPYONLY)
  AlbanyCreateTest (${testName}_suite_A5 input_suite_A5.yaml
    LABELS "LandIce;Tpetra;Forward"
  )

  # -------------------------------------- #
  #     Ian Hewitt's rectancular ramp      #
  # -------------------------------------- #
  configure_file (${CMAKE_CURRENT_SOURCE_DIR}/input_hewitt.yaml
                  ${CMAKE_CURRENT_BINARY_DIR}/input_hewitt.yaml COPYONLY)
  AlbanyCreateTest (${testName}_hewitt input_hewitt.yaml
    LABELS "LandIce;Tpetra;Forward"
  )
endif()
