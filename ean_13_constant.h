//
// Created by Intent on 2020/12/11.
//

#ifndef EAN_13_EAN_13_CONSTANT_H
#define EAN_13_EAN_13_CONSTANT_H

// 开始和结束字符标识: 101
static const int EAN_13_START_TAG = 5;
// 开始和结束字符标识长度
static const int EAN_13_START_TAG_LENGTH = 3;
// 中间标识: 01010
static const int EAN_13_CENTER_TAG = 10;
// 7个二进制组成一个字符
static const int EAN_13_CHAR_LENGTH = 7;
// 4个块组成一个字符
static const int EAN_13_CHAR_BLOCK_LENGTH = 4;
// EAN-13黑白条总长度
static const int EAN_13_LENGTH = 59;
// 单个黑白条的总长度：101 + 7 * 12 + 101 + 01010 = 3 + 7 * 12 + 3 + 5 = 95
static const int EAN_13_BLOCK_LENGTH = 95;
// 白条总长度
static const int EAN_13_WHITE_COUNT = 29;
// 黑条总长度
static const int EAN_13_BLACK_COUNT = 30;
// CODE_PATTERN 长度
static const int EAN_13_CODE_PATTERN_LENGTH = 10;

static const uchar L_CODE_PATTERN[] = {
        13,// 0, 0001101
        25,// 1, 0011001
        19,// 2, 0010011
        61,// 3, 0111101
        35,// 4, 0100011
        49,// 5, 0110001
        47,// 6, 0101111
        59,// 7, 0111011
        55,// 8, 0110111
        11,// 9, 0001011
};

static const uchar L_CODE_PATTERN_LENGTH[][4] = {
        {3, 2, 1, 1},// 0, 0001101
        {2, 2, 2, 1},// 1, 0011001
        {2, 1, 2, 2},// 2, 0010011
        {1, 4, 1, 1},// 3, 0111101
        {1, 1, 3, 2},// 4, 0100011
        {1, 2, 3, 1},// 5, 0110001
        {1, 1, 1, 4},// 6, 0101111
        {1, 3, 1, 2},// 7, 0111011
        {1, 2, 1, 3},// 8, 0110111
        {3, 1, 1, 2},// 9, 0001011
};

static const uchar G_CODE_PATTERN[] = {
        39,// 0, 0100111
        51,// 1, 0110011
        27,// 2, 0011011
        33,// 3, 0100001
        29,// 4, 0011101
        57,// 5, 0111001
        5, // 6, 0000101
        17,// 7, 0010001
        9, // 8, 0001001
        23,// 9, 0010111
};

static const uchar G_CODE_PATTERN_LENGTH[][4] = {
        {1, 1, 2, 3},// 0, 0100111
        {1, 2, 2, 2},// 1, 0110011
        {2, 2, 1, 2},// 2, 0011011
        {1, 1, 4, 1},// 3, 0100001
        {2, 3, 1, 1},// 4, 0011101
        {1, 3, 2, 1},// 5, 0111001
        {4, 1, 1, 1},// 6, 0000101
        {2, 1, 3, 1},// 7, 0010001
        {3, 1, 2, 1},// 8, 0001001
        {2, 1, 1, 3},// 9, 0010111
};

static const uchar R_CODE_PATTERN[] = {
        114,// 0, 1110010
        102,// 1, 1100110
        108,// 2, 1101100
        66, // 3, 1000010
        92, // 4, 1011100
        78, // 5, 1001110
        80, // 6, 1010000
        68, // 7, 1000100
        72, // 8, 1001000
        116,// 9, 1110100
};

static const uchar R_CODE_PATTERN_LENGTH[][4] = {
        {3, 2, 1, 1},// 0, 1110010
        {2, 2, 2, 1},// 1, 1100110
        {2, 1, 2, 2},// 2, 1101100
        {1, 4, 1, 1},// 3, 1000010
        {1, 1, 3, 2},// 4, 1011100
        {1, 2, 3, 1},// 5, 1001110
        {1, 1, 1, 4},// 6, 1010000
        {1, 3, 1, 2},// 7, 1000100
        {1, 2, 1, 3},// 8, 1001000
        {3, 1, 1, 2},// 9, 1110100
};

// EAN 左半部分分布情况
// L-code代表1，G-code代表0
static const uchar EAN_13_STRUCTURE_LEFT[][6] = {
        {1, 1, 1, 1, 1, 1},// 0, LLLLLL, 111111
        {1, 1, 0, 1, 0, 0},// 1, LLGLGG, 110100
        {1, 1, 0, 0, 1, 0},// 2, LLGGLG, 110010
        {1, 1, 0, 0, 0, 1},// 3, LLGGGL, 110001
        {1, 0, 1, 1, 0, 0},// 4, LGLLGG, 101100
        {1, 0, 0, 1, 1, 0},// 5, LGGLLG, 100110
        {1, 0, 0, 0, 1, 1},// 6, LGGGLL, 100011
        {1, 0, 1, 0, 1, 0},// 7, LGLGLG, 101010
        {1, 0, 1, 0, 0, 1},// 8, LGLGGL, 101001
        {1, 0, 0, 1, 0, 1},// 9, LGGLGL, 100101
};

static const uchar EAN_13_CHECK_DIGIT[] = {
        3, 1, 3,
        1, 3, 1, 3,
        1, 3, 1, 3
};

#endif //EAN_13_EAN_13_CONSTANT_H
