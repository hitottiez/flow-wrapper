#!/usr/bin/env bash

set -eux
ROOT=$(cd $(dirname $0);pwd)
RELEASE_DIR=../release
cd ${ROOT}
if [ ! -d build ]; then
    mkdir build
fi
cd build
cmake \
    -D CMAKE_INSTALL_PREFIX=${RELEASE_DIR} \
    ..
make -j$(nproc)
make install

# ライブラリコピー
PYTHON_PKG_PATH=$(python3 -c 'import site; print(site.getsitepackages()[0])')
cp ${ROOT}/release/python/* ${PYTHON_PKG_PATH}