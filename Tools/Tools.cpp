//
// Created by YuSec on 2024/12/6.
//

#include "Tools.h"

string Tools::charToHex(char c) {
    ostringstream oss;
    oss << hex << setw(2) << setfill('0') << static_cast<int>(static_cast<unsigned char>(c));
    return oss.str();
}

vector<vector<unsigned char>> Tools::convertToVectorOfVectors(const vector<unsigned char>& original) {
    vector<vector<unsigned char>> result(4, vector<unsigned char>(4));
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            result[j][i] = original[4 * i + j];
        }
    }
    return result;
}

string Tools::toHexString(vector<unsigned char>& vec) {
    ostringstream oss;

    for (unsigned char byte : vec) {
        // 使用 hex 格式化为十六进制，setw 和 setfill 用于填充零
        oss << charToHex(byte);
    }

    return oss.str();
}

