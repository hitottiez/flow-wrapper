// =============================================================================
// Broxオプティカルフローを計算するためのクラス
// ※現在画像データ(uint8_t)のみ対応
// @author xto-katayama <xto-katayama@tsm.kddi-research.jp>
// =============================================================================
#include <utility>
#include <opencv2/imgproc.hpp>
#include "broxflow.hpp"

namespace ss {

    void BroxFlow::setDevice(int gpu_id) {
        cv::cuda::setDevice(gpu_id);
    }

    void BroxFlow::resetDevice() {
        cv::cuda::resetDevice();
    }

    BroxFlow::BroxFlow() {
        init();
    }

    BroxFlow::BroxFlow(double alpha, double gamma, double scale_factor,
                       int inner_iterations, int outer_iterations, int solver_iterations):
        alpha(alpha),
        gamma(gamma),
        scale_factor(scale_factor),
        inner_iterations(inner_iterations),
        outer_iterations(outer_iterations),
        solver_iterations(solver_iterations)
    {
        init();
    }


    cv::Mat BroxFlow::calc(const cv::Mat& src0, const cv::Mat& src1) {
        using cv::cuda::GpuMat;
        // グレースケールに変換
        cv::Mat gsrc0, gsrc1;
        cv::cvtColor(src0, gsrc0, cv::COLOR_BGR2GRAY);
        cv::cvtColor(src1, gsrc1, cv::COLOR_BGR2GRAY);

        // GpuMatに置き換え
        GpuMat d_frame0(gsrc0);
        GpuMat d_frame1(gsrc1);
        GpuMat d_flow(gsrc0.size(), CV_32FC2);
        GpuMat d_frame0f, d_frame1f;
        // 0.0～1.0にキャスト
        d_frame0.convertTo(d_frame0f, CV_32F, 1.0 / 255.0);
        d_frame1.convertTo(d_frame1f, CV_32F, 1.0 / 255.0);

        // BroxOpticalflow計算
        brox->calc(d_frame0f, d_frame1f, d_flow);

        // 2枚の画像データにする
        cv::Mat flow(d_flow);
        return std::move(flow);
    }

    void BroxFlow::init() {
        brox = cv::cuda::BroxOpticalFlow::create(alpha, gamma, scale_factor, inner_iterations, outer_iterations, solver_iterations);
    }

}
