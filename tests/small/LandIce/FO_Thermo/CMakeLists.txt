get_filename_component(testNameRoot ${CMAKE_CURRENT_SOURCE_DIR} NAME)

if (ALBANY_PARALELL_EXODUS)
  set (USE_SERIAL_MESH "true")
else ()
  # If there's no Iopx, we *must* have ALBANY_DECOMP defined (to decompose the mesh)
  # OR execute with only one rank.
  if (ALBANY_MPI AND NOT ${ALBANY_SEACAS_PATH})
    MESSAGE (FATAL_ERROR "Error! Cannot execute FO_GIS tests in parallel without Iopx or decomp from Trilinos.\n")
  endif()
 set (USE_SERIAL_MESH "false")
endif()

# If Iopx is not present, we must decompose the input mesh first
if (NOT ALBANY_PARALELL_EXODUS AND ALBANY_MPI)
  set (decompMesh TRUE)
endif()

if (ALBANY_EPETRA)

  # Copy input file from source to binary dir
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_FO_Thermo_dry_bed_test.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_FO_Thermo_dry_bed_test.yaml)
                 
  # Copy input file from source to binary dir
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_FO_Thermo_wet_bed_test.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_FO_Thermo_wet_bed_test.yaml)
                 
  # Copy input file from source to binary dir
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_FO_Thermo_Humboldt_fluxDiv.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_FO_Thermo_Humboldt_fluxDiv.yaml)

  # Create the tests
  set (testName ${testNameRoot}_Dry_Bed)
  AlbanyCreateTest (${testName} input_FO_Thermo_dry_bed_test.yaml
    LABELS "LandIce;Epetra;Forward"
  )
  
  set (testName ${testNameRoot}_Wet_Bed)
  AlbanyCreateTest (${testName} input_FO_Thermo_wet_bed_test.yaml
    LABELS "LandIce;Epetra;Forward"
  )
  
  set (testName ${testNameRoot}_Humboldt_fluxDiv)
  # If Iopx is not present, we must decompose the input mesh first
  if (decompMesh)
    add_test (NAME FO_GIS_HUMBOLDT_decompMesh
            COMMAND ${SEACAS_DECOMP} -processors ${MPIMNP} humboldt_2d.exo
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../AsciiMeshes/Humboldt)
    set_tests_properties (FO_GIS_HUMBOLDT_decompMesh PROPERTIES FIXTURES_SETUP humboldtMeshSetup)
  endif()

  AlbanyCreateTest (${testName} input_FO_Thermo_Humboldt_fluxDiv.yaml
    LABELS            "LandIce;Epetra;Forward"
    FIXTURES_REQUIRED_IF decompMesh humboldtMeshSetup)
endif()

# Copy input file from source to binary dir
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_FO_Thermo_wet_bed_test_fea.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/input_FO_Thermo_wet_bed_test_fea.yaml)

# Create the tests
set (testName ${testNameRoot}_Wet_Bed_FEA)
AlbanyCreateTest (${testName} input_FO_Thermo_wet_bed_test_fea.yaml
  LABELS "LandIce;Tpetra;Forward"
)

if (ALBANY_FROSCH)
  # Copy input file from source to binary dir
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_FO_Thermo_wet_bed_test_FROSch.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_FO_Thermo_wet_bed_test_FROSch.yaml)

  # Create the tests
  set (testName ${testNameRoot}_Wet_Bed_FROSch)
  AlbanyCreateTest (${testName} input_FO_Thermo_wet_bed_test_FROSch.yaml
    LABELS "LandIce;Tpetra;Forward;FROSch"
  )
endif()

if(PYTHON_TEST AND ALBANY_FROSCH)
  set(TESTFILES
    hessian_comparison.py
    humboldt_analysis.yaml
    humboldt_analysis_contiguous.yaml
    H-ref-000.mm H-ref-000_contiguous.mm
    ${PYTHON_TEST_HELPERS_DIR}/__init__.py
    ${PYTHON_TEST_HELPERS_DIR}/matrix_reader.py
  )
  file(COPY ${TESTFILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

  set (testName_Contiguous ${testNameRoot}_Contiguous_Mesh_Hessian)
  add_test (${testName_Contiguous}_Serial "${PYTHON_EXECUTABLE}" "hessian_comparison.py" "${SerialAlbanyAnalysis.exe}" "humboldt_analysis_contiguous.yaml" "H-ref-000_contiguous.mm")
  set_tests_properties(${testName_Contiguous}_Serial PROPERTIES LABELS "LandIce;Tpetra;Hessian")

  set (testName_Non_Contiguous ${testNameRoot}_Non_Contiguous_Mesh_Hessian)
  add_test (${testName_Non_Contiguous}_Serial "${PYTHON_EXECUTABLE}" "hessian_comparison.py" "${SerialAlbanyAnalysis.exe}" "humboldt_analysis.yaml" "H-ref-000.mm")
  set_tests_properties(${testName_Non_Contiguous}_Serial PROPERTIES LABELS "LandIce;Tpetra;Hessian")
  set_tests_properties(${testName_Non_Contiguous}_Serial PROPERTIES DEPENDS  ${testName_Contiguous}_Serial)

  if(ALBANY_MPI)
    add_test (${testName_Contiguous}_Parallel "${PYTHON_EXECUTABLE}" "hessian_comparison.py" "${AlbanyAnalysis.exe}"  "humboldt_analysis_contiguous.yaml" "H-ref-000_contiguous.mm")
    set_tests_properties(${testName_Contiguous}_Parallel PROPERTIES LABELS "LandIce;Tpetra;Hessian")
    # Prevent the two tests to be run at the same time as they rely on written files:
    set_tests_properties(${testName_Contiguous}_Parallel PROPERTIES DEPENDS  ${testName_Non_Contiguous}_Serial)
    
    add_test (${testName_Non_Contiguous}_Parallel "${PYTHON_EXECUTABLE}" "hessian_comparison.py" "${AlbanyAnalysis.exe}"  "humboldt_analysis.yaml" "H-ref-000.mm")
    set_tests_properties(${testName_Non_Contiguous}_Parallel PROPERTIES LABELS "LandIce;Tpetra;Hessian")
    # Prevent the two tests to be run at the same time as they rely on written files:
    set_tests_properties(${testName_Non_Contiguous}_Parallel PROPERTIES DEPENDS  ${testName_Contiguous}_Parallel)
  endif()
endif()
