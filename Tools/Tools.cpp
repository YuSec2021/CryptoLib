//
// Created by YuSec on 2024/12/6.
//

#include "Tools.h"


string Tools::charToHex(unsigned char c) {
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

unsigned int Tools::hexStringToInt(string str, int format) {
    unsigned int res = stoi(str, nullptr, format);
    return res;
}

// 左移
vector<unsigned char> Tools::left_shift(std::vector<unsigned char> vec, size_t shift) {
    if (shift == 0) {
        return vec;
    }

    size_t byte_shift = shift / 8; // 移动的字节数
    size_t bit_shift = shift % 8;  // 字节内移动的位数

    // 创建并初始化结果容器
    std::vector<unsigned char> result(vec.size() + byte_shift, 0);

    for (size_t i = 0; i < vec.size(); ++i) {
        result[i] |= (vec[i] << bit_shift);  // 第i个字节左移n位
        if (i + 1 < vec.size()) {
            result[i] |= (vec[i + 1] >> (8 - bit_shift)); // 第i+1个字节右移8-n位
        }
    }

    if (vec[0] >> (8 - bit_shift)) {
        result.insert(result.begin(), 1); // 在最前面插入一个字节
        result[0] = (vec[0] >> (8 - bit_shift));
    }

    return result;
}

// 右移
vector<unsigned char> Tools::right_shift(vector<unsigned char> vec, size_t shift) {
    if (shift == 0) {
        return vec;
    }

    size_t byte_shift = shift / 8; // 移动的字节数
    size_t bit_shift = shift % 8;  // 字节内移动的位数

    if (byte_shift >= vec.size()) {
        return vector<unsigned char>(0); // 全部移出
    }

    vector<unsigned char> result(vec.size() - byte_shift, 0);

    for (size_t i = 0; i < result.size(); ++i) {
        result[i] |= (vec[i + byte_shift] >> bit_shift);
        if (i > 0) {
            result[i] |= (vec[i + byte_shift - 1] << (8 - bit_shift));
        }
    }
    return result;
}

// 辅助函数：打印vector<unsigned char>的十六进制表示
void Tools::print_hex(const vector<unsigned char>& vec) {
    cout << "0x";
    for (unsigned char byte : vec) {
        cout << hex << setw(2) << setfill('0') << static_cast<int>(byte);
    }
    cout << dec << endl; // 恢复十进制输出
}

