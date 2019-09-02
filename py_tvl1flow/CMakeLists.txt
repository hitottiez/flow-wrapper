
add_library(py_tvl1flow SHARED py_tvl1flow.cpp)
target_link_libraries(py_tvl1flow
    ${Flow_Util_LIBRARIES}
    ${PBCVT_LIBRARIES}
    ${TVL1FLOW_LIBRARIES}
    ${OpenCV_LIBS}
    ${PYTHON3_LIBRARIES}
    ${Boost_LIBRARIES}
)

set_target_properties(py_tvl1flow PROPERTIES PREFIX "")
set_target_properties(py_tvl1flow PROPERTIES SUFFIX ".so")

install(TARGETS py_tvl1flow DESTINATION python)
