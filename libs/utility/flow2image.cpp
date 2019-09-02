// =============================================================================
// Opticalflowを画像に変換する等、各種ユーティリティ
// =============================================================================

#include <vector>
#include <opencv2/imgproc.hpp>
#include "flow2image.hpp"

namespace ss {
    static const int OPF_NORM = 16;

    bool isFlowCorrect(cv::Point2f u) {
        return !cvIsNaN(u.x) && !cvIsNaN(u.y) && fabs(u.x) < 1e9 && fabs(u.y) < 1e9;
    }

    // オプティカルフローの計算結果から画素ごとに色変換する
    cv::Vec3b computeColor(float flowX, float flowY) {
        const float rad = sqrt(flowX * flowX + flowY * flowY);
        cv::Vec3b pix;
        float opt;
        opt     = 128 + OPF_NORM *flowX;
        opt     = opt>255 ? 255 : opt;
        opt     = opt < 0 ? 0 : opt;
        pix[2]  = static_cast<uchar>(opt);
        opt     = 128 + OPF_NORM *flowY;
        opt     = opt>255 ? 255 : opt;
        opt     = opt < 0 ? 0 : opt;
        pix[1]  = static_cast<uchar>(opt);
        opt     = rad;
        opt     = 128 + OPF_NORM *opt;
        opt     = opt>255 ? 255 : opt;
        opt     = opt < 0 ? 0 : opt;
        pix[0]  = static_cast<uchar>(opt);
        return pix;
    }
    // 描画を行う
    void flow2image(const cv::Mat& flow, cv::Mat& dst) {
        dst.create(flow.size(), CV_8UC3);
	    dst.setTo(cv::Scalar::all(128));
        auto height = flow.rows;
        auto width = flow.cols;
        flow.forEach<cv::Vec2f>([&](const cv::Vec2f& p, const int position[2]) -> void {
            int y = position[0];
            int x = position[1];
            float flow_x = p[0];
            float flow_y = p[1];
            cv::Point2f flowXy(flow_x, flow_y);
            if (isFlowCorrect(flowXy)) {
                dst.at<cv::Vec3b>(y, x) = computeColor(flow_x, flow_y);
            }
        });
        return ;
    }

    void flow2image2CH(const cv::Mat& flow, cv::Mat& dst, double bound) {
        double lowerBound = -bound;
        double higherBound = bound;
        dst.create(flow.size(), CV_8UC2);
        dst.setTo(cv::Scalar::all(128));
        auto height = flow.rows;
        auto width = flow.cols;
        flow.forEach<cv::Vec2f>([&](const cv::Vec2f& p, const int position[2]) -> void {
            int y = position[0];
            int x = position[1];
            float flow_x = p[0];
            float flow_y = p[1];
            dst.at<cv::Vec2b>(y, x)[0] = boundCast(flow_x, lowerBound, higherBound);
            dst.at<cv::Vec2b>(y, x)[1] = boundCast(flow_y, lowerBound, higherBound);
        });
        return;
    }

    uchar boundCast(double v, double L, double H) {
        return ((v) > (H) ? 255 : (v) < (L) ? 0 : cvRound(255*((v) - (L))/((H)-(L))));
    }
}
