#!/usr/bin/env python
#-*- coding: utf-8 -*-
import sys
import os
THIS_DIR = os.path.dirname(__file__)
PYOP_PATH = os.path.abspath(os.path.join(THIS_DIR, '../release/python'))
sys.path.append(PYOP_PATH)

import cv2
import time

import argparse
parser = argparse.ArgumentParser()
parser.add_argument('--mode', type=str, choices=['brox', 'tvl1'], default='tvl1', help='flow_mode')
parser.add_argument('--outtype', type=str, choices=['rgb', 'xy'], default='xy', help='output flow image type')
parser.add_argument('--no-display', action='store_true', help='no display flag')
args = parser.parse_args()

def flow_extractor_factory(mode):
    """
    TVL1、Brox、どちらを使うか
    @todo fastflowも同じ感じでクラス化したい
    """
    if mode == 'brox':
        import py_broxflow
        flow_extractor = py_broxflow.BroxFlow()
    elif mode == 'tvl1':
        import py_tvl1flow
        flow_extractor = py_tvl1flow.TVL1Flow()
    return flow_extractor

flow_extractor = flow_extractor_factory(args.mode)

video = cv2.VideoCapture(0)
video.set(cv2.CAP_PROP_FRAME_WIDTH, 320)
video.set(cv2.CAP_PROP_FRAME_HEIGHT, 240)
prev_frame = None
while True:
    ret, frame = video.read()
    current_time = time.time()
    if not ret:
        break
    if prev_frame is not None:
        if args.outtype =='rgb':
            # 3CH Color Output
            op_frame = flow_extractor.calc(prev_frame, frame)
            if not args.no_display:
                cv2.imshow('flow', op_frame)
        elif args.outtype == 'xy':
            # 2CH Grauscale Output
            op_frame = flow_extractor.calc2CH(prev_frame, frame)
            flow_x = op_frame[:, :, 0]
            flow_y = op_frame[:, :, 1]
            if not args.no_display:
                cv2.imshow('flow_x', flow_x)
                cv2.imshow('flow_y', flow_y)
    fps = 1 / (time.time() - current_time)
    print('FPS: {:f}'.format(fps))
    key = cv2.waitKey(1) & 0xff
    if key == 27 or key == ord('q'):
        break
    prev_frame = frame
