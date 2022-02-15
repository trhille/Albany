# Name the test with the directory name
get_filename_component(testNameRoot ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# This variable will be set in the input files during the 'configure_file' call
if (ALBANY_PARALELL_EXODUS)
  set (USE_SERIAL_MESH "true")
#IKT 5/22/19 - commenting out for now as this is leading to compilation error
else ()
  # If there's no Iopx, we *must* have ALBANY_DECOMP defined (to decompose the mesh)
  # OR execute with only one rank.
  if (ALBANY_MPI AND NOT ${ALBANY_SEACAS_PATH})
    MESSAGE (FATAL_ERROR "Error! Cannot execute FO_GIS tests in parallel without Iopx or decomp from Trilinos.\n")
  endif()
 set (USE_SERIAL_MESH "false")
endif()

# If Iopx is not present, we must decompose the input mesh files first
if (NOT ALBANY_PARALELL_EXODUS AND ALBANY_MPI)
  set (decompMesh TRUE)
endif()

###########################################
###     Import 2d ascii mesh (test)     ###
###########################################

set (testName ${testNameRoot}_Import2DAsciiMesh)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_create_exo_from_msh.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/input_create_exo_from_msh.yaml)
 
if (ALBANY_PARALELL_EXODUS AND ALBANY_MPI)
  AlbanyCreateTest (${testName} input_create_exo_from_msh.yaml  
    LABELS "LandIce"
  )  
endif ()

AlbanyCreateTest (${testName}_Serial input_create_exo_from_msh.yaml
  SERIAL LABELS "LandIce"
)

####################################
###     Populate mesh (test)     ###
####################################

set (testName ${testNameRoot}_PopulateMeshes)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_populate_meshes.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_populate_meshes.yaml)

# If Iopx is not present, we must decompose the input mesh first
if (decompMesh)
  add_test (NAME FO_GIS_decompMesh
            COMMAND ${SEACAS_DECOMP} -processors ${MPIMNP} gis_unstruct_2d.exo
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../ExoMeshes)
  set_tests_properties (FO_GIS_decompMesh PROPERTIES
    FIXTURES_SETUP meshSetup RUN_SERIAL TRUE)
endif()

AlbanyCreateTest (${testName} input_fo_gis_populate_meshes.yaml
  LABELS "LandIce;Epetra;Forward"
  FIXTURES_SETUP PopulateMeshes
  FIXTURES_REQUIRED_IF decompMesh meshSetup
)

####################################
###        Unstruct tests        ###
####################################

set (testName ${testNameRoot}_Unstructured)

if (ALBANY_EPETRA)
  # First run
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_unstruct.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_unstruct.yaml)
  AlbanyCreateTest (${testName}_Epetra input_fo_gis_unstruct.yaml
    LABELS            "LandIce;Epetra;Forward"
    FIXTURES_REQUIRED PopulateMeshes
    FIXTURES_SETUP    UnstructRestart
  )

  # Restart
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_unstruct_restart.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_unstruct_restart.yaml)
  AlbanyCreateTest (${testName}_Restart input_fo_gis_unstruct_restart.yaml
    LABELS "LandIce;Epetra;Forward"
    RUN_SERIAL TRUE
    FIXTURES_REQUIRED UnstructRestart
  )
endif()

if (ALBANY_ifPACK2)
  # Normal run
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_unstructT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_unstructT.yaml)
  AlbanyCreateTest (${testName}_Tpetra input_fo_gis_unstructT.yaml
    LABELS "LandIce;Tpetra;Forward"
    FIXTURES_REQUIRED PopulateMeshes
  )

  # Memoization run
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_unstruct_memT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_unstruct_memT.yaml)
  AlbanyCreateTest (${testName}_Memoization input_fo_gis_unstruct_memT.yaml
    LABELS "LandIce;Tpetra;Forward"
    FIXTURES_REQUIRED PopulateMeshes
  )
endif()

if (decompMesh)
  add_test (NAME FO_GIS_HUMBOLDT_decompMesh
        COMMAND ${SEACAS_DECOMP} -processors ${MPIMNP} humboldt_2d.exo
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../AsciiMeshes/Humboldt)
  set_tests_properties (FO_GIS_HUMBOLDT_decompMesh PROPERTIES FIXTURES_SETUP humboldtMeshSetup)
endif()

if (ALBANY_FROSCH)
  # Normal run
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_unstructT_FROSch.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_unstructT_FROSch.yaml)
  AlbanyCreateTest (${testName}_Tpetra_FROSch
    input_fo_gis_unstructT_FROSch.yaml
    LABELS "LandIce;Tpetra;Forward"
    FIXTURES_REQUIRED PopulateMeshes
  )
  
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_humboldt_frosch_fluxdiv.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_humboldt_frosch_fluxdiv.yaml)
  AlbanyCreateTest (${testNameRoot}_Humboldt_FluxDiv_Tpetra_FROSch
    input_fo_humboldt_frosch_fluxdiv.yaml
    LABELS            "LandIce;Tpetra;Forward"
    FIXTURES_REQUIRED_IF decompMesh humboldtMeshSetup
  )

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_humboldt_frosch_power_law.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_humboldt_frosch_power_law.yaml)
  AlbanyCreateTest (${testNameRoot}_Humboldt_powerLaw_Tpetra_FROSch
    input_fo_humboldt_frosch_power_law.yaml
    LABELS            "LandIce;Tpetra;Forward"
    FIXTURES_REQUIRED_IF decompMesh humboldtMeshSetup
  )


  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_humboldt_frosch_effect_press.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_humboldt_frosch_effect_press.yaml)
  AlbanyCreateTest (${testNameRoot}_Humboldt_effectPress_Tpetra_FROSch
    input_fo_humboldt_frosch_effect_press.yaml
    LABELS            "LandIce;Tpetra;Forward"
    FIXTURES_REQUIRED_IF decompMesh humboldtMeshSetup
  )
endif()

if (ALBANY_MUELU)
  # Normal run
  
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_humboldt_muelu.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_humboldt_muelu.yaml)
  AlbanyCreateTest (${testNameRoot}_Humboldt_Tpetra_MueLu
    input_fo_humboldt_muelu.yaml
    LABELS            "LandIce;Epetra;Forward"
    FIXTURES_REQUIRED_IF decompMesh humboldtMeshSetup
  )
endif()


####################################
###          20km tests          ###
####################################

set (testName ${testNameRoot}_Gis20km)
if (ALBANY_EPETRA) 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis20km_test.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis20km_test.yaml)

  AlbanyCreateTest (${testName}_Epetra input_fo_gis20km_test.yaml
    LABELS "LandIce;Epetra;Forward"
  )
endif()

if (ALBANY_ifPACK2)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis20km_testT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis20km_testT.yaml)

  AlbanyCreateTest (${testName}_Tpetra input_fo_gis20km_testT.yaml
    LABELS "LandIce;Tpetra;Forward"
  )
endif()

####################################
###    Coupled Thickness tests   ###
####################################

if (ALBANY_MESH_DEPENDS_ON_SOLUTION)
  # LB: Disabling this test for now, since ever since we merged #412 it no longer works
  #     To be clear, before merging #412 it passed, but it was computing the wrong thing...

  # set (testName ${testNameRoot}_CoupledThicknessShapeOpt)

  # if (ALBANY_EPETRA)
  #   configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_coupled_shape_opt.yaml
  #                  ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_coupled_shape_opt.yaml)

  #   AlbanyCreateTest (${testName}_Epetra input_fo_gis_coupled_shape_opt.yaml
  #     LABELS "LandIce;Epetra;Forward"
  #   )
  # endif()
  # if (ALBANY_ifPACK2)
  #   configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_coupled_shape_optT.yaml
  #                  ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_coupled_shape_optT.yaml)

  #   AlbanyCreateTest (${testName}_Tpetra input_fo_gis_coupled_shape_optT.yaml
  #     LABELS "LandIce;Tpetra;Forward"
  #   )
  # endif()
else()
  set (testName ${testNameRoot}_CoupledThickness)

  if (ALBANY_EPETRA)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_coupled.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_coupled.yaml)

    AlbanyCreateTest (${testName}_Epetra input_fo_gis_coupled.yaml
      LABELS "LandIce;Epetra;Forward"
    )
  endif()

  if(NOT ALBANY_ENABLE_CUDA)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_coupledT.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_coupledT.yaml)

    AlbanyCreateTest (${testName}_Tpetra input_fo_gis_coupledT.yaml
      LABELS "LandIce;Tpetra;Forward"
    )
  endif()
endif()

####################################
###  Adjoint Sensitivity tests   ###
####################################

set (testName ${testNameRoot}_AdjointSensitivity)

# Tetra
if (ALBANY_EPETRA)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_adjoint_sensitivity.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_adjoint_sensitivity.yaml)
  AlbanyCreateTest (${testName}_Epetra input_fo_gis_adjoint_sensitivity.yaml
    LABELS "LandIce;Epetra;Forward"
  )
endif()

if (ALBANY_ifPACK2)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_adjoint_sensitivityT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_adjoint_sensitivityT.yaml)
  AlbanyCreateTest (${testName}_Tpetra input_fo_gis_adjoint_sensitivityT.yaml
    LABELS "LandIce;Tpetra;Forward"
  )

  set (testName ${testNameRoot}_ForwardSensitivity)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_forward_sensitivityT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_forward_sensitivityT.yaml)
  AlbanyCreateTest (${testName}_Tpetra input_fo_gis_forward_sensitivityT.yaml
    LABELS "LandIce;Tpetra;Forward"
  )
endif()

# Wedge
set (testName ${testNameRoot}_AdjointSensitivity_Wedge)

if (ALBANY_EPETRA)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_wedge_adjoint_sensitivity.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_wedge_adjoint_sensitivity.yaml)
  AlbanyCreateTest (${testName} input_fo_gis_wedge_adjoint_sensitivity.yaml
    LABELS "LandIce;Epetra;Forward"
  )
endif()

# Basal friction sensitivity
set (testName ${testNameRoot}_AdjointSensitivity_BasalFriction_FluxDivergence)

if (ALBANY_ifPACK2)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_analysis_betaT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_analysis_betaT.yaml)
  AlbanyCreateTest (${testName}_Tpetra input_fo_gis_analysis_betaT.yaml
    LABELS "LandIce;Tpetra;Forward"
  )

  if (ALBANY_ROL)
    set (testName ${testNameRoot}_Analysis_BasalFriction)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_analysis_betaT.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_analysis_betaT.yaml)
    AlbanyCreateTest (${testName} input_fo_gis_analysis_betaT.yaml
      ANALYSIS LABELS "LandIce;Tpetra;Analysis;ROL"
    )

    set (testName ${testNameRoot}_Analysis_BasalFriction_Memoization)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_analysis_beta_memT.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_analysis_beta_memT.yaml)
    AlbanyCreateTest (${testName} input_fo_gis_analysis_beta_memT.yaml
      ANALYSIS LABELS "LandIce;Tpetra;Analysis;ROL"
    )

    set (testName ${testNameRoot}_Analysis_BasalFriction_Hessian)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_analysis_beta_hessianT.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_analysis_beta_hessianT.yaml)
    AlbanyCreateTest (${testName} input_fo_gis_analysis_beta_hessianT.yaml
      ANALYSIS LABELS "LandIce;Tpetra;Analysis;ROL"
    )
  endif()
endif()

# Basal friction and stiffening factor sensitivity
set (testName ${testNameRoot}_AdjointSensitivity_StiffeningBasalFriction)

if (ALBANY_EPETRA)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_analysis_stiffening.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_analysis_stiffening.yaml)
  AlbanyCreateTest (${testName}_Epetra input_fo_gis_analysis_stiffening.yaml
    LABELS "LandIce;Epetra;Forward"
  )
endif()

if (ALBANY_ifPACK2)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_analysis_stiffeningT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_analysis_stiffeningT.yaml)
  AlbanyCreateTest (${testName}_Tpetra input_fo_gis_analysis_stiffeningT.yaml
    LABELS "LandIce;Tpetra;Forward"
  )

  if (ALBANY_ROL)
    set (testName ${testNameRoot}_Analysis_StiffeningBasalFriction)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_analysis_stiffeningT.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_analysis_stiffeningT.yaml)
    AlbanyCreateTest (${testName} input_fo_gis_analysis_stiffeningT.yaml
      ANALYSIS LABELS "LandIce;Tpetra;Analysis;ROL"
    )

    set (testName ${testNameRoot}_Analysis_StiffeningBasalFriction_Memoization)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_analysis_stiffening_memT.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_analysis_stiffening_memT.yaml)
    AlbanyCreateTest (${testName} input_fo_gis_analysis_stiffening_memT.yaml
      ANALYSIS LABELS "LandIce;Tpetra;Analysis;ROL"
    )
  endif()
endif()

if (ALBANY_MESH_DEPENDS_ON_PARAMETERS)
  # Thickness sensitivity
  set (testName ${testNameRoot}_AdjointSensitivity_Thickness)
  if (ALBANY_EPETRA)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_adjoint_sensitivity_thickness.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_adjoint_sensitivity_thickness.yaml)
    AlbanyCreateTest (${testName}_Epetra
      input_fo_gis_adjoint_sensitivity_thickness.yaml
      LABELS "LandIce;Epetra;Forward"
    )
  endif()

  if (ALBANY_ifPACK2)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_adjoint_sensitivity_thicknessT.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_adjoint_sensitivity_thicknessT.yaml)
    AlbanyCreateTest (${testName}_Tpetra
      input_fo_gis_adjoint_sensitivity_thicknessT.yaml
      LABELS "LandIce;Tpetra;Forward"
    )
    
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_adjoint_sensitivity_bed_and_topT.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_adjoint_sensitivity_bed_and_topT.yaml)
    AlbanyCreateTest (${testName}_MoveSurfHeightAndBed
      input_fo_gis_adjoint_sensitivity_bed_and_topT.yaml
      LABELS "LandIce;Tpetra;Forward"
    )

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_adjoint_sensitivity_thickness_adjustSurfHeightT.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_adjoint_sensitivity_thickness_adjustSurfHeightT.yaml)
    AlbanyCreateTest (${testName}_MoveSurfHeight
      input_fo_gis_adjoint_sensitivity_thickness_adjustSurfHeightT.yaml
      LABELS "LandIce;Tpetra;Forward"
    )
  endif()

  # Two parameters sensitivity
  set (testName ${testNameRoot}_AdjointSensitivity_TwoParameters)
  if (ALBANY_EPETRA)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_analysis_two_params.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_analysis_two_params.yaml)
    AlbanyCreateTest (${testName}_Epetra input_fo_gis_analysis_two_params.yaml
      LABELS "LandIce;Epetra;Forward"
    )
  endif()

  if (ALBANY_ifPACK2)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_analysis_two_paramsT.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_analysis_two_paramsT.yaml)
    AlbanyCreateTest (${testName}_Tpetra input_fo_gis_analysis_two_paramsT.yaml
      LABELS "LandIce;Tpetra;Forward"
    )
  endif()
endif()

####################################
###     Sensitivity SMB tests    ###
####################################

set (testName ${testNameRoot}_SensSMBwrtBeta)

if (ALBANY_EPETRA)
  # First run
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_beta_smb.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_beta_smb.yaml)
  AlbanyCreateTest (${testName}_Epetra input_fo_gis_beta_smb.yaml
    LABELS "LandIce;Epetra;Forward"
    FIXTURES_SETUP ${testName}_firstRun
  )

  # Restart
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_beta_smb_restart.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_beta_smb_restart.yaml)

  AlbanyCreateTest (${testName}_Restart input_fo_gis_beta_smb_restart.yaml
    FIXTURES_REQUIRED ${testName}_firstRun
    LABELS "LandIce;Epetra;Forward"
  )
endif()

if (ALBANY_ifPACK2)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_beta_smbT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_beta_smbT.yaml)
  AlbanyCreateTest (${testName}_Tpetra input_fo_gis_beta_smbT.yaml
    LABELS "LandIce;Tpetra;Forward"
  )
endif()

####################################
###        Manifold tests        ###
####################################

if (ALBANY_EPETRA)
  set (testName ${testNameRoot}_Manifold)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_manifold.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_manifold.yaml)

  AlbanyCreateTest (${testName} input_fo_gis_manifold.yaml
    LABELS "LandIce;Epetra;Forward"
  )
endif()

####################################
###   Laplacian sampling tests   ###
####################################

if (ALBANY_EPETRA)
  set (testName ${testNameRoot}_LaplacianPriorSampling)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis_sampling.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis_sampling.yaml)
  AlbanyCreateTest (${testName} input_fo_gis_sampling.yaml
    LABELS "LandIce;Epetra;Forward"
  )
endif()
