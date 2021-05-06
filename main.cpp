#include <iostream>
#include "resources.h"
#include "barcode.h"
#include "ean_13.h"
#include "code_36.h"

using namespace std;

int main(int argc, char **argv) {
    cv::Mat mat;
//    if (argc > 1) {
//        mat = cv::imread(argv[1]);
//    } else {
    mat = cv::imread(TEST_CODE_36_1);
//    }
    if (mat.empty()) {
        std::cout << "src can not be empty!" << std::endl;
        return -1;
    }
    cv::Rect rect = barcode::find(mat);
//    cout << ean_13::recognition(mat, rect) << endl;
    cout << code_36::recognition(mat, rect) << endl;
    return 0;
}