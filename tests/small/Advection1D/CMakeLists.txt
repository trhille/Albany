# Name the test with the directory name
get_filename_component(testName ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Copy Input file from source to binary dir
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_scalar_param_fwd_sens_implicit.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/input_scalar_param_fwd_sens_implicit.yaml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_scalar_param_adjoint_sens_explicit.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/input_scalar_param_adjoint_sens_explicit.yaml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_with_source_dist_param_adjoint_sens_explicit_consistentM.yaml
	       ${CMAKE_CURRENT_BINARY_DIR}/input_with_source_dist_param_adjoint_sens_explicit_consistentM.yaml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_with_source_dist_param_adjoint_sens_explicit_lumpedM.yaml
     	       ${CMAKE_CURRENT_BINARY_DIR}/input_with_source_dist_param_adjoint_sens_explicit_lumpedM.yaml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_with_source_dist_param_adjoint_sens_implicit.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/input_with_source_dist_param_adjoint_sens_implicit.yaml COPYONLY)

# Create the test with this name and standard executable
AlbanyCreateTest (${testName}_Scalar_Param_Fwd_Sens_Implicit
  input_scalar_param_fwd_sens_implicit.yaml
  LABELS "Demo;Tpetra;Forward;Serial")

AlbanyCreateTest (${testName}_Scalar_Param_Adjoint_Sens_Explicit
  input_scalar_param_adjoint_sens_explicit.yaml
  LABELS "Demo;Tpetra;Adjoint;Serial"
)

AlbanyCreateTest (${testName}_with_Source_Dist_Param_Adjoint_Sens_Explicit_ConsistentM
  input_with_source_dist_param_adjoint_sens_explicit_consistentM.yaml
  SERIAL LABELS "Demo;Tpetra;Adjoint;Serial"
)

AlbanyCreateTest (${testName}_with_Source_Dist_Param_Adjoint_Sens_Explicit_LumpedM
  input_with_source_dist_param_adjoint_sens_explicit_lumpedM.yaml
  SERIAL LABELS "Demo;Tpetra;Adjoint;Serial"
)

AlbanyCreateTest (${testName}_with_Source_Dist_Param_Adjoint_Implicit
  input_with_source_dist_param_adjoint_sens_implicit.yaml
  SERIAL LABELS "Demo;Tpetra;Forward;Serial"
)
