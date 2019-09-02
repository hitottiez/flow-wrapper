// =============================================================================
// Broxオプティカルフローを計算するためのクラス
// ※現在画像データ(uint8_t)のみ対応
// @author xto-katayama <xto-katayama@tsm.kddi-research.jp>
// =============================================================================
#include <utility>
#include <opencv2/imgproc.hpp>
#include "tvl1flow.hpp"

namespace ss {

    void TVL1Flow::setDevice(int gpu_id) {
        cv::cuda::setDevice(gpu_id);
    }

    void TVL1Flow::resetDevice() {
        cv::cuda::resetDevice();
    }

    TVL1Flow::TVL1Flow() {
        init();
    }

    cv::Mat calc(const cv::Mat& src0, const cv::Mat& src1);


    cv::Mat TVL1Flow::calc(const cv::Mat& src0, const cv::Mat& src1) {
        using cv::cuda::GpuMat;
        // グレースケールに変換
        cv::Mat gsrc0, gsrc1;
        cv::cvtColor(src0, gsrc0, cv::COLOR_BGR2GRAY);
        cv::cvtColor(src1, gsrc1, cv::COLOR_BGR2GRAY);

        // GpuMatに置き換え
        GpuMat d_frame0(gsrc0);
        GpuMat d_frame1(gsrc1);
        GpuMat d_flow(gsrc0.size(), CV_32FC2);
        // GpuMat d_frame0f, d_frame1f;
        // 0.0～1.0にキャスト
        // d_frame0.convertTo(d_frame0f, CV_32F, 1.0 / 255.0);
        // d_frame1.convertTo(d_frame1f, CV_32F, 1.0 / 255.0);

        // BroxOpticalflow計算
        tvl1->calc(d_frame0, d_frame1, d_flow);

        cv::Mat flow(d_flow);
        return std::move(flow);
    }

    void TVL1Flow::init() {
        tvl1 = cv::cuda::OpticalFlowDual_TVL1::create();
    }

}
