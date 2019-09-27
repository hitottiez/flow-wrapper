# OpenCV Optical Flow API Wrapper
## Overview
This library is a wrapper of OpenCV optical flow API (GPUver) on Python3.

### Optical flow list
- BroxFlow
- TVL1Opticalflow

### Output
- RGB color image
- X/Y grayscale image

### Usage
refer examples/flow_webcam.py

## Requirements
- CUDA
- Python (==ver3.5)
- OpenCV (==ver4.x **WITH_CUDA=ON**)
- Boost.Python (>1.68.0)
- cmake (>=2.8)

## Install
Clone this repository:
```bash
$ git clone --recurslve <My repository URL>
```

Install:
```bash
$ ./build.sh
```

## Directory structure
- examples
    - sample codes
- libs
    - libraries
- py_broxflow
    - Python wrapepr of BroxFlow
- py_fastflow
    - Python wrapepr of FastFlow
- py_tvl1flow
    - Python wrapepr of TVL1Opticalflow
