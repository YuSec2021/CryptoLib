//
// Created by YuSec on 2024/12/6.
//

#include "MD5.h"

size_t MD5::check(unsigned char a) {
    for (size_t i = 1; i < 8; i++) {
        if (a >> i && a >> (i+1) == 0) {
            return i;
        }
    }
    return 1;
}

void MD5::padding(vector<unsigned char> &data) {
    int res = (data.size() - 1) * 8 + this->check(data[0]);
    res %= 512;

    size_t bits = 0;
    if (res >= 448) {
        bits = 448 + (512 - res);
    } else {
        bits = 448 - res;
    }
    if (bits > 1) { // 需要补的尾数大于1
        data = Tools::left_shift(data, 1);
        data[data.size()-1] ^= 0x1;
    }
    data = Tools::left_shift(data, bits-1);
}

void MD5::blockText(vector<unsigned char> &data) {

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