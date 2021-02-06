#include "code_128.h"

std::string code_128::recognition(cv::Mat &src, cv::Rect &rect) {
    cv::Mat temp(src, rect);
    cv::cvtColor(temp, temp, cv::COLOR_BGR2GRAY);
    // 中值滤波，消除椒盐噪声
    cv::medianBlur(temp, temp, 3);
    cv::threshold(temp, temp, 128, 255, cv::THRESH_BINARY);
//    cv::rectangle(src, rect, cv::Scalar(0, 0, 255), 1);
//    imshow("src", src);
//    cv::waitKey();
    // 取1/3到2/3之间的条形码
    for (int i = temp.cols / 3; i < temp.cols / 3 * 2; ++i) {
        auto line = temp.ptr<uchar>(i);
        // 找到最小值
        code_128::barcode_info info = get_min_unit(line, temp.cols);
        // 转换为vector
        std::vector<float> barcode_data = convert(line, info);
        // 解码
        std::string ret = decode(barcode_data);
        if (!ret.empty()) {
            return ret;
        }
    }
    return std::string();
}

code_128::barcode_info code_128::get_min_unit(const uchar *line, int width) {
    code_128::barcode_info info{};
    // 是否找到头
    bool is_find_head = false;
    int char_sum = 0;
    // 前11个黑白条的值
    uchar prev_array[CODE_128_CHAR_LENGTH];
    std::set<int> continue_unit_set{};
    for (int i = 0; i < width;) {
        int startValue = line[i];
        int continueUnit = 1;
        while (i != width - 1 && line[i + 1] == startValue) {
            continueUnit++;
            i++;
        }
        // 找到开头
        if (!is_find_head) {
            bool is_pattern = true;
            for (int j = 0; j < CODE_128_CHAR_LENGTH - 1; ++j) {
                if (prev_array[j] != CODE_128_START_PATTERN[j]) {
                    is_pattern = false;
                    break;
                }
            }
            if (is_pattern && startValue == CODE_128_STOP_PATTERN[CODE_128_CHAR_LENGTH - 1]) {
                is_find_head = true;
                info.start_pos = i - CODE_128_CHAR_LENGTH - 1;
                char_sum = CODE128_CHAR_LEN;
                continue_unit_set.insert(continueUnit);
            }
        } else if (is_find_head) {
            char_sum += continueUnit;
            continue_unit_set.insert(continueUnit);
            bool is_pattern = true;
            // 找到结尾
            for (int j = 0; j < CODE_128_CHAR_LENGTH - 1; ++j) {
                if (prev_array[j] != CODE_128_STOP_PATTERN[j]) {
                    is_pattern = false;
                    break;
                }
            }
            if (is_pattern && startValue == CODE_128_STOP_PATTERN[CODE_128_CHAR_LENGTH - 1]) {
                info.stop_pos = i + 1;
                break;
            }
        }
        // 前11个黑白条数组移位
        for (int j = CODE_128_CHAR_LENGTH - 1; j > 0; --j) {
            prev_array[j] = prev_array[j - 1];
        }
        prev_array[0] = startValue;
        info.stop_pos = i + 1;
        i++;
    }
//    info.min_unit = (int) round((float) char_sum / EAN_13_BLOCK_LENGTH);
    if (info.min_unit == 0) {
        info.min_unit = 1;
    }
    return info;
}

std::string code_128::decode(const std::vector<float> &data) {
    if (data.size() < CODE_128_MIN_LENGTH) {
        return std::string();
    }
    // 去除掉头
    int start = CODE128_CHAR_LEN;
    std::vector<code_128::barcode_ret> ret;
    std::string barcode;
    int check_sum = 0;
    int count = 1;
    int check_digit = 0;
    // 权值
    float weight_sum = 0;
    for (int i = start; i < data.size();) {
        float a[CODE_128_CHAR_BLOCK_LENGTH];
        for (int j = 0; j < CODE_128_CHAR_BLOCK_LENGTH; ++j) {
            a[j] = data[i++];
        }
        int code = global_euclidean_distance(a, weight_sum);
        check_digit = code;
        barcode += std::to_string(code);
        check_sum += count * code;
        count++;
    }
//    check_sum += x;
    int current_check_digit = 10 - (check_sum % 10);
    if (current_check_digit == 10) {
        current_check_digit = 0;
    }
//        std::cout << check_digit << "," << check_sum << "," << current_check_digit << ","
//                  << weight_sum << "," << ret.size() << std::endl;
    if (check_digit == current_check_digit) {
        ret.push_back({
                              .weight_sum = weight_sum,
                              .barcode = barcode
                      });
    }
    if (!ret.empty()) {
        float weight_sum = ret[0].weight_sum;
        std::string barcode = ret[0].barcode;
        for (auto r : ret) {
            if (r.weight_sum < weight_sum) {
                barcode = r.barcode;
            }
        }
        return barcode;
    }
    return std::string();
}

std::vector<float> code_128::convert(const uchar *line, code_128::barcode_info info) {
    std::vector<float> ret;
    for (int i = info.start_pos; i < info.stop_pos; i++) {
        int startValue = line[i];
        float continueUnit = 1;
        while (i != info.stop_pos - 1 && line[i + 1] == startValue) {
            continueUnit++;
            i++;
        }
        float count = continueUnit / (float) info.min_unit;
        ret.push_back(count);
    }
    return ret;
}

int code_128::global_euclidean_distance(const float *a, float &weight) {
    float ret[CODE_128_CODE_PATTERN_LENGTH];
    for (int z = 0; z < CODE_128_CODE_PATTERN_LENGTH; ++z) {
        float sum = 0;
        for (int i = 0; i < CODE_128_CHAR_BLOCK_LENGTH; ++i) {
            sum += pow(a[i] - (float) CODE_128_PATTERN[z][i], 2);
        }
        ret[z] = sqrt(sum) + 0.5 * local_euclidean_distance(z, a);
    }
    float min = ret[0];
    int index = 0;
    for (int i = 1; i < CODE_128_CODE_PATTERN_LENGTH; i++) {
        if (ret[i] < min) {
            index = i;
            min = ret[i];
        }
    }
    weight += min;
    return index;
}

float code_128::local_euclidean_distance(int index, const float *a) {
    float sum = 0;
    for (int i = 0; i < 5; ++i) {
        float temp = 0;
        for (int j = i; j <= i + 1; ++j) {
            temp += a[j] - (float) CODE_128_PATTERN[index][j];
        }
        sum += pow(temp, 2);
    }
    return sqrt(sum);
}
