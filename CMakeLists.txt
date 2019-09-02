cmake_minimum_required(VERSION 2.8)

project(CV_CPP_DEMO)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O3 -msse4")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wno-unknown-pragmas -Wall -msse4")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_SHARED_LINKER_FLAGS "-shared -fPIC")

if (NOT CUDA_TOOKLIT_ROOT_DIR)
    set(CUDA_TOOKLIT_ROOT_DIR /usr/local/cuda)
endif()
if(NOT NUMPY_INCLUDE_DIRS)
    set(NUMPY_INCLUDE_DIRS /usr/local/lib/python3.5/dist-packages/numpy/core/include)
endif()

# OpenCV追加
find_package(OpenCV REQUIRED)

# Eigen3追加
find_package(Eigen3 REQUIRED)

# Python3読み込み(pkg-configで)
find_package(PkgConfig)
pkg_check_modules(PYTHON3 REQUIRED python3)
# Boostライブラリ読み込み
find_package(Boost REQUIRED COMPONENTS system python35 numpy35)

include_directories(
    ${PYTHON3_INCLUDE_DIRS}
    ${NUMPY_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

# vendor libraries
add_subdirectory(libs)
include_directories(
    ${TVL1FLOW_INCLUDE_DIR}
    ${Broxflow_INCLUDE_DIR}
    ${Flow_Util_INCLUDE_DIR}
    ${PBCVT_INCLUDE_DIR}
)

# Applications
add_subdirectory(py_broxflow)
add_subdirectory(py_tvl1flow)