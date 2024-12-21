//
// Created by YuSec on 2024/12/6.
//

#include "MD5.h"

#include <cstdint>

size_t MD5::check(unsigned char a) {
    for (size_t i = 1; i < 8; i++) {
        if (a >> i && a >> (i+1) == 0) {
            return i + 1;
        }
    }
    return 1;
}

void MD5::padding(vector<unsigned char> &data) {
    uint64_t originalSize = data.size();
    unsigned int res = (data.size() - 1) * 8 + this->check(data[0]);
    res %= 512;
    size_t bits = 0;
    if (res >= 448) {
        bits = 512 - res % 448;
    } else {
        bits = 448 - res;
    }

    // 拆分两次进行左移，先左移1位，将该为置1
    data = Tools::left_shift(data, 1);
    data[data.size()-1] ^= 0x1;
    bits -= 1;
    data = Tools::left_shift(data, bits);

    // 插入原始信息长度
    vector<unsigned char> MessageSize = Tools::uint64ToVector(originalSize);
    data.insert(data.end(), MessageSize.begin(), MessageSize.end());

}

void MD5::blockText(vector<unsigned char> &data) {
    size_t groupCount = data.size() * 8 / 512;

    vector<vector<unsigned char>> groups(groupCount);
    // for (size_t i = 0; i < groupCount; i++) {
    //     groups[i] =
    // }
}



unsigned int MD5::F(unsigned int a, unsigned int b, unsigned int c) {
    return (a & b) | ((~a) & c);
}

unsigned int MD5::G(unsigned int a, unsigned int b, unsigned int c) {
    return (a & c) | (b & (~c));
}

unsigned int MD5::H(unsigned int a, unsigned int b, unsigned int c) {
    return a ^ b ^ c;
}

unsigned int MD5::I(unsigned int a, unsigned int b, unsigned int c) {
    return b ^ (a | (~c));
}

unsigned int MD5::FF(unsigned int a, unsigned int b, unsigned int c,
            unsigned int d, unsigned int M, unsigned int s, unsigned int t) {
    return b + (a + this->F(b,c,d) + M + t);
}

unsigned int MD5::GG(unsigned int a, unsigned int b, unsigned int c,
    unsigned int d, unsigned int M, unsigned int s, unsigned int t) {
    return b + (a + this->G(b, c, d) + M + t);
}

unsigned int MD5::HH(unsigned int a, unsigned int b, unsigned int c,
    unsigned int d, unsigned int M, unsigned int s, unsigned int t) {
    return b + (a + this->H(b, c, d) + M + t);
}

unsigned int MD5::II(unsigned int a, unsigned int b, unsigned int c,
    unsigned int d, unsigned int M, unsigned int s, unsigned int t) {
    return b + (a + this->I(b, c, d) + M + t);
}