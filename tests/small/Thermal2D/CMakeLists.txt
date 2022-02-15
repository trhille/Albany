if(NOT ALBANY_PARALLEL_ONLY)
  # Name the test with the directory name
  get_filename_component(testName ${CMAKE_CURRENT_SOURCE_DIR} NAME)

  # Copy Input file from source to binary dir
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_steady.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_steady.yaml COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_be_with_source_scalar_param_fwd_sens.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_be_with_source_scalar_param_fwd_sens.yaml COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_be_with_source_scalar_param_adjoint_sens.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_be_with_source_scalar_param_adjoint_sens.yaml COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_be_with_source_dist_param_adjoint_sens.yaml
          ${CMAKE_CURRENT_BINARY_DIR}/input_be_with_source_dist_param_adjoint_sens.yaml COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fe_with_source.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fe_with_source.yaml COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fe_with_source_dist_param_adjoint_sens.yaml
          ${CMAKE_CURRENT_BINARY_DIR}/input_fe_with_source_dist_param_adjoint_sens.yaml COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/compute_errs_source_no_movie2avi.m
                 ${CMAKE_CURRENT_BINARY_DIR}/compute_errs_source_no_movie2avi.m COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_backward_euler.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_backward_euler.yaml COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_forward_euler.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_forward_euler.yaml COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_gerk.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_gerk.yaml COPYONLY)

  # Create the test with this name and standard executable
  AlbanyCreateTest (${testName}_BackwardEuler input_backward_euler.yaml
    LABELS "Demo;Tpetra;Forward"
  )

  AlbanyCreateTest (${testName}_ForwardEuler input_forward_euler.yaml
    LABELS "Demo;Tpetra;Forward"
  )
endif()

AlbanyCreateTest (${testName}_ForwardEuler_with_Source input_fe_with_source.yaml
  LABELS "Demo;Tpetra;Forward"
)

AlbanyCreateTest (${testName}_BackwardEuler_with_Source_Scalar_Param_Fwd_Sens 
  input_be_with_source_scalar_param_fwd_sens.yaml
  LABELS "Demo;Tpetra;Forward"
)

AlbanyCreateTest (${testName}_BackwardEuler_with_Source_Scalar_Param_Adjoint_Sens
  input_be_with_source_scalar_param_fwd_sens.yaml
  LABELS "Demo;Tpetra;Forward"
)

AlbanyCreateTest (${testName}_BackwardEuler_with_Source_Dist_Param_Adjoint_Sens
  input_be_with_source_dist_param_adjoint_sens.yaml
  SERIAL LABELS "Demo;Tpetra;Adjoint;Serial"
)

AlbanyCreateTest (${testName}_ForwardEuler_with_Source_Dist_Param_Adjoint_Sens
  input_fe_with_source_dist_param_adjoint_sens.yaml
  SERIAL LABELS "Demo;Tpetra;Adjoint;Serial"
)

