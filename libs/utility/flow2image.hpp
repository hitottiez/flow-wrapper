#ifndef SS_FLOW2IMAGE_H
#define SS_FLOW2IMAGE_H

// =============================================================================
// Opticalflowを画像に変換する等、各種ユーティリティ
// =============================================================================

#include <opencv2/core.hpp>

namespace ss {

    /**
     * [isFlowCorrect description]
     * @param  u [description]
     * @return   [description]
     */
    bool isFlowCorrect(cv::Point2f u);

    /**
     * 画素を計算
     * @param  flowX オプティカルフローx方向
     * @param  flowY オプティカルフローy方向
     * @return       ピクセル値
     */
    cv::Vec3b computeColor(float flowX, float flowY);

    /**
     * オプティカルフローを画像に変換する
     * @param flow [description]
     * @param dst  [description]
     */
    void flow2image(const cv::Mat& flow, cv::Mat& dst);

    /**
     * オプティカルフローを2ch画像に変換する
     * @param flow オプティカルフロー結果
     * @param dst 出力画像
     * @param bound 有効なオプティカルフローの最低値／最大値(±boundまで有効)
     */
    void flow2image2CH(const cv::Mat& flow, cv::Mat& dst, double bound=20.0);

    /**
     * オプティカルフローの計算結果を、0〜255の値に変換する(flow2image2CH用)
     * @param v 値
     * @param L 最低値
     * @param H 最大値
     */
    uchar boundCast(double v, double L, double H);
}

#endif
