//
// Created by Intent on 2021/4/25.
//

#include "code_36.h"

std::string code_36::recognition(cv::Mat &src, cv::Rect &rect) {
    cv::Mat temp(src, rect);
    cv::cvtColor(temp, temp, cv::COLOR_BGR2GRAY);
    // 中值滤波，消除椒盐噪声
    cv::medianBlur(temp, temp, 3);
    cv::threshold(temp, temp, 128, 255, cv::THRESH_BINARY);
    // 分为baseShare等份
    float baseShare = 20.0F;
    float startPoint = 0.2F;
    float centerPoint = 0.5F;
    float endPoint = 0.8F;
    float oneShare = (float) temp.cols / baseShare;
    for (int i = (int) (oneShare * (baseShare * startPoint));
         i < (int) (oneShare * (baseShare * (endPoint + 0.1F))); ++i) {
        if (i > (int) (oneShare * (baseShare * startPoint))
            && i < (int) (oneShare * (baseShare * (startPoint + 0.1F)))
            || i > (int) (oneShare * (baseShare * centerPoint))
               && i < (int) (oneShare * (baseShare * (centerPoint + 0.1F)))
            || i > (int) (oneShare * (baseShare * endPoint))
               && i < (int) (oneShare * (baseShare * (endPoint + 0.1F)))) {
            auto line = temp.ptr<uchar>(i);
            // 找到最小值
            barcode::barcode_info info = get_min_unit(line, temp.cols);
        }
    }

    return std::string();
}

barcode::barcode_info code_36::get_min_unit(const uchar *line, int width) {
    barcode::barcode_info info{};
    barcode::print_line(line, width);
    return info;
}