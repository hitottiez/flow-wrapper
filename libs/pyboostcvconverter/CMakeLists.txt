

add_library(
    pbcvt STATIC
    pbcvt/src/pyboost_cv2_converter.cpp
    pbcvt/src/pyboost_cv3_converter.cpp
    pbcvt/src/pyboost_cv4_converter.cpp
)

target_include_directories(pbcvt PUBLIC pbcvt/include)

set(PBCVT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/include PARENT_SCOPE)
set(PBCVT_LIBRARIES pbcvt PARENT_SCOPE)

install(TARGETS pbcvt DESTINATION lib)
install(FILES pbcvt/include/pyboostcvconverter/pyboostcvconverter.hpp DESTINATION include/pyboostcvconverter/)
