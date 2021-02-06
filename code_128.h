#ifndef CODE_128_H
#define CODE_128_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include "code_128_constant.h"

class code_128 {
public:
    struct barcode_info {
        // 开始的位置
        int start_pos;
        // 结束的位置
        int stop_pos;
        // 平均单位
        int min_unit;
    };

    struct barcode_ret {
        // 权值和
        float weight_sum;
        // 条形码
        std::string barcode;
    };

    static std::string recognition(cv::Mat &src, cv::Rect &rect);


    static int global_euclidean_distance(const float *a, float &weight);

private:
    static code_128::barcode_info get_min_unit(const uchar *line, int width);

    static std::string decode(const std::vector<float> &barcode_data);

    static std::vector<float> convert(const uchar *line, code_128::barcode_info info);

    static float local_euclidean_distance(int index, const float *a);
};

#endif