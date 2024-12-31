//
// Created by YuSec on 2024/12/6.
//

#include "Tools.h"


string Tools::charToHex(uint8_t c) {
    ostringstream oss;
    oss << hex << setw(2) << setfill('0') << static_cast<int>(static_cast<uint8_t>(c));
    return oss.str();
}

vector<vector<uint8_t>> Tools::convertToVectorOfVectors(const vector<uint8_t>& original) {
    vector<vector<uint8_t>> result(4, vector<uint8_t>(4));
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            result[j][i] = original[4 * i + j];
        }
    }
    return result;
}

string Tools::toHexString(vector<uint8_t>& vec) {
    ostringstream oss;
    for (uint8_t byte : vec) {
        // 使用 hex 格式化为十六进制，setw 和 setfill 用于填充零
        oss << charToHex(byte);
    }

    return oss.str();
}


vector<uint8_t> Tools::uint64ToVector(uint64_t value) {
    vector<uint8_t> vec(8); // 创建一个大小为8的vector，足够存放64位数据

    // 将uint64_t的每个字节提取到vector中
    for (size_t i = 0; i < 8; ++i) {
        vec[i] = static_cast<uint8_t>((value >> ((7 - i) * 8)) & 0xFF); // 提取每个字节
    }

    return vec;
}

unsigned int Tools::hexStringToInt(string str, int format) {
    unsigned int res = stoi(str, nullptr, format);
    return res;
}

// 左移
vector<uint8_t> Tools::left_shift(std::vector<uint8_t> vec, size_t shift) {
    if (shift == 0) {
        return vec;
    }

    size_t byte_shift = shift / 8; // 移动的字节数
    size_t bit_shift = shift % 8;  // 字节内移动的位数

    // 创建并初始化结果容器
    std::vector<uint8_t> result(vec.size() + byte_shift, 0);

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
vector<uint8_t> Tools::right_shift(vector<uint8_t> vec, size_t shift) {
    if (shift == 0) {
        return vec;
    }

    size_t byte_shift = shift / 8; // 移动的字节数
    size_t bit_shift = shift % 8;  // 字节内移动的位数

    if (byte_shift >= vec.size()) {
        return vector<uint8_t>(0); // 全部移出
    }

    vector<uint8_t> result(vec.size() - byte_shift, 0);

    for (size_t i = 0; i < result.size(); ++i) {
        result[i] |= (vec[i + byte_shift] >> bit_shift);
        if (i > 0) {
            result[i] |= (vec[i + byte_shift - 1] << (8 - bit_shift));
        }
    }
    return result;
}

// 辅助函数：打印vector<uint8_t>的十六进制表示
void Tools::print_hex(const vector<uint8_t>& vec) {
    cout << "0x";
    for (uint8_t byte : vec) {
        cout << hex << setw(2) << setfill('0') << static_cast<int>(byte);
    }
    cout << dec << endl; // 恢复十进制输出
}

uint32_t Tools::rotate_left(uint32_t value, uint8_t shift) {
    const int bits = 32;
    shift %= bits;
    return (value << shift) | (value >> (bits - shift));
}

uint32_t Tools::rotate_right(uint32_t value, uint8_t shift) {
    const int bits = 32;
    shift %= bits;
    return (value >> shift) | (value << (bits - shift));
}

uint32_t Tools::swapEndian(uint32_t x) {
    return ((x >> 24) & 0xff) |
        ((x >> 8) & 0xff00) |
        ((x << 8) & 0xff0000) |
        ((x << 24) & 0xff000000);
}
