//
// Created by YuSec on 2024/12/6.
//

#include "MD5.h"

void MD5::padding(vector<unsigned char> &data) {
    int res = data.size() * 8 % 512;
    if (res == 448) {

    } else {
        
    }
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
    a = b + (a + this->F(b,c,d) + M + t);
}

unsigned int MD5::GG(unsigned int a, unsigned int b, unsigned int c,
    unsigned int d, unsigned int M, unsigned int s, unsigned int t) {
    a = b + (a + this->G(b, c, d) + M + t);
}

unsigned int MD5::HH(unsigned int a, unsigned int b, unsigned int c,
    unsigned int d, unsigned int M, unsigned int s, unsigned int t) {
    a = b + (a + this->H(b, c, d) + M + t);
}

unsigned int MD5::II(unsigned int a, unsigned int b, unsigned int c,
    unsigned int d, unsigned int M, unsigned int s, unsigned int t) {
    a = b + (a + this->I(b, c, d) + M + t);
}