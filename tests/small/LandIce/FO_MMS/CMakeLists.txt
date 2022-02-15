# Name the test with the directory name
get_filename_component(testNameRoot ${CMAKE_CURRENT_SOURCE_DIR} NAME)

####################################
###       SinCosGlen tests       ###
####################################

set(testName ${testNameRoot}_SincCosGlen)

if (ALBANY_EPETRA) 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_sincos2D.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_sincos2D.yaml COPYONLY)

  AlbanyCreateTest (${testName}_Epetra input_fo_sincos2D.yaml
    LABELS "LandIce;Epetra;Forward"
  )
endif()

if (ALBANY_ifPACK2)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_sincos2DT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_sincos2DT.yaml COPYONLY)

  AlbanyCreateTest (${testName}_Tpetra input_fo_sincos2DT.yaml
    LABELS "LandIce;Tpetra;Forward"
  )
endif()

####################################
###   SinCos3DPeriodicXY tests   ###
####################################

set(testName ${testNameRoot}_SincCos3DPeriodicXY)

if (ALBANY_EPETRA) 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_sincosz.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_sincosz.yaml COPYONLY)
  AlbanyCreateTest (${testName}_Epetra input_fo_sincosz.yaml
    DEFAULT_TIMEOUT LABELS "LandIce;Epetra;Forward"
  )
endif()

if (ALBANY_ifPACK2)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_sincoszT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_sincoszT.yaml COPYONLY)
  AlbanyCreateTest (${testName}_Tpetra input_fo_sincoszT.yaml
    DEFAULT_TIMEOUT LABELS "LandIce;Tpetra;Forward"
  )
endif()

####################################
###         SinExp tests         ###
####################################

set(testName ${testNameRoot}_SinExp_Neumann)

if (ALBANY_EPETRA) 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_sinexp_neumann.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_sinexp_neumann.yaml COPYONLY)
  AlbanyCreateTest (${testName}_Epetra input_fo_sinexp_neumann.yaml
    DEFAULT_TIMEOUT LABELS "LandIce;Epetra;Forward"
  )
endif()

if (ALBANY_ifPACK2)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_sinexp_neumannT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_sinexp_neumannT.yaml COPYONLY)
  AlbanyCreateTest (${testName}_Tpetra input_fo_sinexp_neumannT.yaml
    DEFAULT_TIMEOUT LABELS "LandIce;Epetra;Forward"
  )
endif()

####################################
###       CosExp Basal tests     ###
####################################

set(testName ${testNameRoot}_CosExp_Basal)

if (ALBANY_EPETRA) 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_cosexp_basal.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_cosexp_basal.yaml COPYONLY)

  AlbanyCreateTest (${testName}_Epetra input_fo_cosexp_basal.yaml
    DEFAULT_TIMEOUT LABELS "LandIce;Epetra;Forward"
  )
endif()

if (ALBANY_ifPACK2)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_cosexp_basalT.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_fo_cosexp_basalT.yaml COPYONLY)

  AlbanyCreateTest (${testName}_Tpetra input_fo_cosexp_basalT.yaml
    DEFAULT_TIMEOUT LABELS "LandIce;Epetra;Forward"
  )
endif()

####################################
###    CosExp Basal all tests    ###
####################################

if(ALBANY_SEACAS)

  set(testName ${testNameRoot}_CosExp_BasalAll)

  if (ALBANY_EPETRA) 
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_cosexp_basal_all_glensLaw.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input_fo_cosexp_basal_all_glensLaw.yaml COPYONLY)

    AlbanyCreateTest (${testName}_Epetra input_fo_cosexp_basal_all_glensLaw.yaml
      SERIAL LABELS "LandIce;Epetra;Forward"
    )
  endif()

  if (ALBANY_ifPACK2)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_cosexp_basal_all_glensLawT.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input_fo_cosexp_basal_all_glensLawT.yaml COPYONLY)

    AlbanyCreateTest (${testName}_Tpetra input_fo_cosexp_basal_all_glensLawT.yaml
      SERIAL LABELS "LandIce;Tpetra;Forward"
    )
  endif()
endif()

####################################
###     Grounding Line tests     ###
####################################

if (ALBANY_PANZER_EXPR_EVAL)
  set(testName ${testNameRoot}_FO_GLF)

  # Quads
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_glf_quad.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_glf_quad.yaml COPYONLY)

  AlbanyCreateTest (${testName}_QUAD input_glf_quad.yaml
    SERIAL LABELS "LandIce;Tpetra;Forward"
  )

  # Triangles
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_glf_tri.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_glf_tri.yaml COPYONLY)

  AlbanyCreateTest (${testName}_TRI input_glf_tri.yaml
    SERIAL LABELS "LandIce;Tpetra;Forward"
  )

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_glf_tri_edge_on_gl.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_glf_tri_edge_on_gl.yaml COPYONLY)

  # Triangles, corner case
  AlbanyCreateTest (${testName}_TRI_CORNER_CASE input_glf_tri_edge_on_gl.yaml
    SERIAL LABELS "LandIce;Tpetra;Forward"
  )

  if (ALBANY_PAMGEN)
    # Triangles, nonconst velocity
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_glf_tri_nonconst_vel.yaml
                   ${CMAKE_CURRENT_BINARY_DIR}/input_glf_tri_nonconst_vel.yaml COPYONLY)

    AlbanyCreateTest (${testName}_TRI_NONCONST_VELOCITY input_glf_tri_nonconst_vel.yaml
      SERIAL LABELS "LandIce;Tpetra;Forward"
    )
  endif()
endif()

###################################################
###     Surface Mass Balance Mismatch tests     ###
###################################################

if (ALBANY_PANZER_EXPR_EVAL)
  set(testName ${testNameRoot}_FO_SMB)

  # Quads
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_smb_quad.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_smb_quad.yaml COPYONLY)

  AlbanyCreateTest (${testName}_QUAD input_smb_quad.yaml
    SERIAL LABELS "LandIce;Tpetra;Forward"
  )

  if (ALBANY_PAMGEN)
    # Triangles, nonconst velocity
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_smb_tri.yaml
                 ${CMAKE_CURRENT_BINARY_DIR}/input_smb_tri.yaml COPYONLY)

    AlbanyCreateTest (${testName}_TRI input_smb_tri.yaml
      SERIAL LABELS "LandIce;Tpetra;Forward"
    )
  endif()
endif()

