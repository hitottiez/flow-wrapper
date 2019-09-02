# OpenCV Optical Flow API Wrapper

## 概要

OpenCVのBroxFlowとTVL1OpticalflowのGPU版をPython3で使用するためのライブラリです。

### 利用可能なオプティカルフロー

* BroxFlow
* TVL1Opticalflow

### 出力

* RGBカラー画像による出力
* X/Yモノクロ画像による出力

### 使い方

* examples/flow_webcam.pyを参照

## 動作条件

* CUDA
* Python (==ver3.5)
* OpenCV (==ver4.x **WITH_CUDA=ON**)
* Boost.Python (>1.68.0)
* cmake (>=2.8)

## インストール

まず、本ソースコードを「recursive」オプションをつけてクローンしてください

```bash
$ git clone --recurslve <My repository URL>
```

build.shを実行するとインストールできます

```bash
$ ./build.sh
```

## ディレクトリ構成

* examples
    * 利用方法サンプルプログラム
* libs
    * 各種ライブラリ
* py_broxflow
    * BroxFlowのPythonラッパー実装
* py_fastflow
    * FastFlowのPythonラッパー実装
* py_tvl1flow
    * TVL1オプティカルフローのPythonラッパー実装
