configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_fo_gis20km_refine.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/input_fo_gis20km_refine.yaml COPYONLY)

#IK, 10/29/13: Convert to tpetra!
if(ALBANY_STK_PERCEPT AND ALBANY_EPETRA)
  AlbanyCreateTest (${testName}_Gis20km_refine input_fo_gis20km_refine.yaml
    NP8
  )
ENDIF()
