//
// Created by Intent on 2021/4/23.
//

#ifndef CODE_36_CONSTANT_H
#define CODE_36_CONSTANT_H

// code 36的字符bit位长度
static const uint8_t CODE_36_CHAR_BIT_LEN = 9;

// code 36开始的bit位
static const uchar CODE_36_START_BIT_PATTERN[] = {
        1, 1, 1, 0, 0, 0, 1, 1, 1
};

static const uchar CODE_36_START_PATTERN[] = {
        3, 3, 3
};

static const uchar CODE_36_STOP_BIT_PATTERN[] = {
        0, 0, 0, 1, 1, 1, 1, 1, 1
};

static const uchar CODE_36_STOP_PATTERN[] = {
        3, 6
};

static const uchar CODE_36_CHAR_BIT_PATTERN[][9] = {
        // 0 - 9
        {0, 0, 0, 1, 0, 0, 1, 1, 1}, // 0
        {0, 0, 0, 1, 1, 1, 0, 0, 1}, // 1
        {0, 0, 0, 1, 0, 0, 0, 0, 1}, // 2
        {0, 0, 0, 1, 1, 1, 0, 1, 1}, // 3
        {0, 0, 1, 0, 0, 0, 0, 1, 1}, // 4
        {0, 1, 1, 1, 0, 0, 0, 1, 1}, // 5
        {0, 0, 1, 0, 0, 1, 1, 1, 1}, // 6
        {0, 1, 1, 1, 0, 1, 1, 1, 1}, // 7
        {0, 0, 0, 1, 0, 0, 0, 1, 1}, // 8
        {0, 0, 1, 0, 0, 0, 1, 1, 1}, // 9
        // A - Z
        {0, 0, 0, 1, 1, 0, 1, 1, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 1},
        {0, 0, 0, 1, 1, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 1, 1, 0, 1},
        {0, 1, 1, 1, 1, 0, 0, 0, 1},
        {0, 0, 1, 1, 0, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 0, 1, 1, 1},
        {0, 0, 0, 0, 1, 0, 0, 1, 1},
        {0, 0, 0, 0, 1, 1, 1, 0, 1},
        {0, 0, 1, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 1, 0, 0, 0, 1},
        {0, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1, 0, 1, 1, 1},
        {0, 1, 1, 1, 0, 0, 1, 1, 1},
        {0, 0, 1, 1, 1, 1, 0, 1, 1},
        {0, 0, 0, 1, 0, 1, 1, 1, 1},
        {0, 1, 1, 1, 0, 0, 0, 0, 1},
        {0, 1, 1, 1, 1, 0, 0, 1, 1},
        {0, 0, 1, 1, 1, 0, 0, 0, 1},
        {0, 0, 1, 1, 1, 0, 0, 1, 1},
        {0, 1, 0, 0, 0, 0, 1, 1, 1},
        {0, 0, 1, 1, 1, 1, 0, 0, 1},
        {0, 0, 1, 1, 0, 0, 1, 1, 1},
        {0, 0, 0, 0, 1, 1, 0, 1, 1},
        {0, 0, 1, 1, 1, 0, 1, 1, 1},
        {0, 0, 0, 0, 1, 1, 0, 0, 1},
        // OTHER
        {0, 1, 1, 0, 0, 1, 1, 1, 1},
        {0, 1, 1, 0, 0, 0, 1, 1, 1},
        {0, 1, 1, 0, 0, 0, 0, 1, 1},
        {0, 1, 0, 0, 0, 1, 1, 1, 1}
};

static const uchar CODE_36_CHAR_PATTERN[][4] = {
        // 0 - 9
        {3, 1, 2, 3},
        {3, 3, 2, 1},
        {3, 1, 4, 1},
        {3, 3, 1, 2},
        {2, 1, 4, 2},
        {1, 3, 3, 2},
        {2, 1, 2, 4},
        {1, 3, 1, 4},
        {3, 1, 3, 2},
        {2, 1, 3, 3},
        // A - Z
        {3, 2, 1, 3},
        {3, 2, 3, 1},
        {3, 2, 2, 2},
        {3, 4, 1, 1},
        {1, 4, 3, 1},
        {2, 2, 1, 4},
        {1, 4, 1, 3},
        {4, 1, 2, 2},
        {4, 3, 1, 1},
        {2, 2, 3, 2},
        {4, 1, 3, 1},
        {2, 2, 4, 1},
        {4, 1, 1, 3},
        {1, 3, 2, 3},
        {2, 4, 1, 2},
        {3, 1, 1, 4},
        {1, 3, 4, 1},
        {1, 4, 2, 2},
        {2, 3, 3, 1},
        {2, 3, 2, 2},
        {1, 1, 4, 3},
        {2, 4, 2, 1},
        {2, 2, 2, 3},
        {4, 2, 1, 2},
        {2, 3, 1, 3},
        {4, 2, 2, 1},
        // OTHER
        {1, 2, 2, 4},
        {1, 2, 3, 3},
        {1, 2, 4, 2},
        {1, 1, 3, 4},
};

#endif //CODE_36_CONSTANT_H
