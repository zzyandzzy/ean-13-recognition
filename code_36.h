//
// Created by Intent on 2021/4/25.
//

#ifndef CODE36_H
#define CODE36_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include "code_36_constant.h"
#include "barcode.h"

class code_36 {
public:
    static std::string recognition(cv::Mat &src, cv::Rect &rect);

private:
    /**
     * 找到最小块的宽度
     * @param line
     * @param width
     * @return
     */
    static barcode::barcode_info get_min_unit(const uchar *line, int width);

    static int global_euclidean_distance(const float *a, bool is_l_code, float &weight);

    static float local_euclidean_distance(int index, const float *a, bool is_l_codeL);
};

#endif //CODE36_H
