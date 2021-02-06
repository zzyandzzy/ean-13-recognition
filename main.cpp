#include <iostream>
#include "resources.h"
#include "ean_13.h"
#include "code_128.h"

using namespace std;

int main(int argc, char **argv) {
    cv::Mat mat;
    if (argc > 1) {
        mat = cv::imread(argv[1]);
    } else {
        mat = cv::imread(TEST_EAN_13_TEST_1);
    }
    if (mat.empty()) {
        std::cout << "src can not be empty!" << std::endl;
        return -1;
    }
    cv::Rect rect = ean_13::find(mat);
    cout << ean_13::recognition(mat, rect) << endl;
    return 0;
}