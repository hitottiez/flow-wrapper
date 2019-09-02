#ifndef SS_BROXFLOW_H
#define SS_BROXFLOW_H
// =============================================================================
// Broxオプティカルフローを計算するためのクラス
// ※現在画像データ(uint8_t)のみ対応
// @author xto-katayama <xto-katayama@tsm.kddi-research.jp>
// =============================================================================

#include <opencv2/core.hpp>
#include <opencv2/cudaoptflow.hpp>
#include <opencv2/cudaarithm.hpp>

namespace ss {

    /**
     * BroxOpticalflowのクラス
     */
    class BroxFlow {
    public:

        /**
         * GPUデバイスをセットする
         * @param gpu_id [description]
         */
        static void setDevice(int gpu_id);

        /**
         * GPUデバイスをリセットする
         */
        static void resetDevice();

        BroxFlow();
        BroxFlow(double alpha, double gamma, double scale_factor,
                 int inner_iterations, int outer_iterations, int solver_iterations);
        cv::Mat calc(const cv::Mat& src0, const cv::Mat& src1);
    private:
        void init();
        double alpha = 0.197;
        double gamma = 50.0;
        double scale_factor = 0.8;
        int inner_iterations = 5;
        int outer_iterations = 150;
        int solver_iterations = 10;
        cv::Ptr<cv::cuda::BroxOpticalFlow> brox;
    };
}

#endif
