
add_library(py_broxflow SHARED py_broxflow.cpp)
target_link_libraries(py_broxflow
    ${Flow_Util_LIBRARIES}
    ${PBCVT_LIBRARIES}
    ${Broxflow_LIBRARIES}
    ${OpenCV_LIBS}
    ${PYTHON3_LIBRARIES}
    ${Boost_LIBRARIES}
)

set_target_properties(py_broxflow PROPERTIES PREFIX "")
set_target_properties(py_broxflow PROPERTIES SUFFIX ".so")

install(TARGETS py_broxflow DESTINATION python)
