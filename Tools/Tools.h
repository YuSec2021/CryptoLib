//
// Created by YuSec on 2024/12/6.
//

#ifndef TOOLS_H
#define TOOLS_H

#include <cstdint>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

class Tools
{
public:
    // Type Transform
    static string charToHex(uint8_t c);
    static string toHexString(vector<uint8_t> &vec);
    static uint32_t hexStringToInt(string str, int format);
    static vector<uint8_t> uint64ToVector(uint64_t value);

    static vector<vector<uint8_t>> convertToVectorOfVectors(const vector<uint8_t>& original);

    static vector<uint8_t> left_shift(vector<uint8_t> vec, size_t shift);
    static vector<uint8_t> right_shift(vector<uint8_t> vec, size_t shift);

    static void print_hex(const vector<uint8_t> &vec);

    // 循环移位
    static uint32_t rotate_left(uint32_t value, uint8_t shift);
    static uint32_t rotate_right(uint32_t value, uint8_t shift);
};



#endif //TOOLS_H
