
# Other Utilities
add_subdirectory(utility)
set(Flow_Util_INCLUDE_DIR ${Flow_Util_INCLUDE_DIR} PARENT_SCOPE)
set(Flow_Util_LIBRARIES ${Flow_Util_LIBRARIES} PARENT_SCOPE)

# Broxflow
add_subdirectory(broxflow)
set(Broxflow_INCLUDE_DIR ${Broxflow_INCLUDE_DIR} PARENT_SCOPE)
set(Broxflow_LIBRARIES ${Broxflow_LIBRARIES} PARENT_SCOPE)

# TVL1flow
add_subdirectory(tvl1flow)
set(TVL1FLOW_INCLUDE_DIR ${TVL1FLOW_INCLUDE_DIR} PARENT_SCOPE)
set(TVL1FLOW_LIBRARIES ${TVL1FLOW_LIBRARIES} PARENT_SCOPE)

# PyBoostCVConverter
add_subdirectory(pyboostcvconverter)
set(PBCVT_INCLUDE_DIR ${PBCVT_INCLUDE_DIR} PARENT_SCOPE)
set(PBCVT_LIBRARIES ${PBCVT_LIBRARIES} PARENT_SCOPE)
