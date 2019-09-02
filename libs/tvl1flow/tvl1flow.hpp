#ifndef SS_TVL1FLOW_H
#define SS_TVL1FLOW_H
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
    class TVL1Flow {
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

        TVL1Flow();
        cv::Mat calc(const cv::Mat& src0, const cv::Mat& src1);
    private:
        void init();
        cv::Ptr<cv::cuda::OpticalFlowDual_TVL1> tvl1;
    };
}

#endif
