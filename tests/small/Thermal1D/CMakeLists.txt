# Name the test with the directory name
get_filename_component(testName ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Copy Input file from source to binary dir
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/input.yaml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_with_source_scalar_param_fwd_sens_implicit.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/input_with_source_scalar_param_fwd_sens_implicit.yaml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_with_source_scalar_param_adjoint_sens_implicit.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/input_with_source_scalar_param_adjoint_sens_implicit.yaml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_with_source_scalar_param_fwd_sens_explicit.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/input_with_source_scalar_param_fwd_sens_explicit.yaml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_with_source_dist_param_adjoint_sens_implicit.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/input_with_source_dist_param_adjoint_sens_implicit.yaml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_with_source_dist_param_adjoint_sens_explicit.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/input_with_source_dist_param_adjoint_sens_explicit.yaml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/compute_errs.m
               ${CMAKE_CURRENT_BINARY_DIR}/compute_errs.m COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/compute_errs_no_movie2avi.m
               ${CMAKE_CURRENT_BINARY_DIR}/compute_errs_no_movie2avi.m COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/compute_errs_source_no_movie2avi.m
               ${CMAKE_CURRENT_BINARY_DIR}/compute_errs_source_no_movie2avi.m COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/plot_exact_soln.m
               ${CMAKE_CURRENT_BINARY_DIR}/plot_exact_soln.m COPYONLY)

# Create the test with this name and standard executable
AlbanyCreateTest (${testName} input.yaml
  LABELS "Demo;Tpetra;Forward"
)

AlbanyCreateTest (${testName}_with_Source_Scalar_Param_Fwd_Sens_Implicit 
  input_with_source_scalar_param_fwd_sens_implicit.yaml
  LABELS "Demo;Tpetra;Forward"
)

AlbanyCreateTest (${testName}_with_Source_Scalar_Param_Adjoint_Sens_Implicit
  input_with_source_scalar_param_adjoint_sens_implicit.yaml
  LABELS "Demo;Tpetra;Adjoint"
)

AlbanyCreateTest (${testName}_with_Source_Dist_Param_Adjoint_Sens_Implicit
  input_with_source_dist_param_adjoint_sens_implicit.yaml
  SERIAL LABELS "Demo;Tpetra;Adjoint;Serial"
)
AlbanyCreateTest (${testName}_with_Source_Dist_Param_Adjoint_Sens_Explicit
  input_with_source_dist_param_adjoint_sens_explicit.yaml
  SERIAL LABELS "Demo;Tpetra;Adjoint;Serial"
)
