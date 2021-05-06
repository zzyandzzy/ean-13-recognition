#include "barcode.h"

cv::Rect barcode::find(cv::Mat &src) {
    if (src.empty()) {
        return cv::Rect();
    }
    cv::Mat outImage;
    cv::Mat imageSobelX, imageSobelY;
//    resize(src, src, cv::Size(720, 1560));
//    resize(src, outImage, Size(src.cols / CODE128_TIMES, src.rows / CODE128_TIMES));
    // 2. 转化为灰度图
    cv::cvtColor(src, outImage, cv::COLOR_RGB2GRAY);
//    imshow("cvt", outImage);
    // 3. 高斯平滑滤波
    cv::GaussianBlur(outImage, outImage, cv::Size(3, 3), 0);
    // 4.求得水平和垂直方向灰度图像的梯度差,使用Sobel算子
    cv::Mat imageX16S, imageY16S;
    cv::Sobel(outImage, imageX16S, CV_16S, 1, 0, 3, 1, 0, 4);
    cv::Sobel(outImage, imageY16S, CV_16S, 0, 1, 3, 1, 0, 4);
    cv::convertScaleAbs(imageX16S, imageSobelX, 1, 0);
    cv::convertScaleAbs(imageY16S, imageSobelY, 1, 0);
    outImage = imageSobelX - imageSobelY;
    // 5.均值滤波，消除高频噪声
    blur(outImage, outImage, cv::Size(7, 7));
//    imshow("blur", outImage);
    // 6.二值化
    cv::threshold(outImage, outImage, 128, 255, cv::THRESH_BINARY);
//    imshow("threshold", outImage);
    // 7.闭运算，填充条形码间隙
    cv::Mat element = getStructuringElement(cv::MORPH_RECT, cv::Size(21, 7));
//    cv::morphologyEx(outImage, outImage, cv::MORPH_CLOSE, element);
//    imshow("ex", outImage);
    element = getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
    // 8. 腐蚀，去除孤立的点
    cv::erode(outImage, outImage, element);
    element = getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
//    imshow("erode", outImage);
    // 9. 膨胀，填充条形码间空隙
    cv::dilate(outImage, outImage, element);
//    imshow("dilate", outImage);
//    cv::waitKey();
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hiera;
    //10.通过findContours找到条形码区域的矩形边界
    cv::findContours(outImage, contours, hiera, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
//    for (int idx = 0; idx >= 0; idx = hiera[idx][0]) {
//        cv::Scalar color(0, 0, 255);
//        drawContours(src, contours, idx, color, 1, cv::LINE_AA, hiera);
//    }
//    imshow("Components", src);
//    cv::waitKey(0);
    cv::Rect rect;
    for (auto &contour : contours) {
        cv::Rect r = boundingRect(contour);
        if (rect.area() < r.area()) {
            rect = r;
        }
    }
    return rect;
}

void barcode::print_vector(const std::vector<float> &barcode_data, barcode::barcode_info info) {
    std::cout << "--------------------------" << std::endl;
//    int newLine = 1;
//    bool is_head = true;
//    int num = 0;
//    for (auto data : barcode_data) {
//        num++;
//        std::cout << data << ",";
//        if (is_head && newLine == EAN_13_START_TAG_LENGTH) {
//            newLine = 1;
//            is_head = false;
//            std::cout << std::endl;
//            continue;
//        }
//        if (num >= 27 && num <= 32) {
//            std::cout << std::endl;
//            newLine = 0;
//        } else {
//            if (newLine == EAN_13_CHAR_BLOCK_LENGTH) {
//                newLine = 0;
//                std::cout << std::endl;
//            }
//        }
//        newLine++;
//    }
    std::cout << std::endl << "--------------------------" << std::endl;
}

void barcode::print_line(const uchar *line, int width) {
    print_line(line, {
            .start_pos = 0,
            .stop_pos = width,
            .min_unit = 1
    });
}

void barcode::print_line(const uchar *line, barcode::barcode_info info) {
    std::cout << "--------------------------" << std::endl;
    int newLine = 1;
    for (int i = info.start_pos; i < info.stop_pos; ++i) {
        std::cout << (int) (line[i] == 255 ? 0 : 1) << ",";
        if (newLine == 9 * info.min_unit) {
            newLine = 0;
            std::cout << std::endl;
        }
        newLine++;
    }
    std::cout << std::endl << "--------------------------" << std::endl;
}
