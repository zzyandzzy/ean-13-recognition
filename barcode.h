#ifndef BARCODE_H
#define BARCODE_H

#include <opencv2/opencv.hpp>

class barcode {
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

    static cv::Rect find(cv::Mat &src);

    static void print_line(const uchar *line, int width);

    static void print_line(const uchar *line, barcode::barcode_info info);

    static void print_vector(const std::vector<float> &barcode_data, barcode::barcode_info info);

};

#endif