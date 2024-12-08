//
// Created by YuSec on 2024/12/6.
//

#include "AES.h"

void AES::encrypt() {

}

void AES::decrypt() {

}


int AES::hexReplace(unsigned char p) {
    unsigned char ridx = p >> 4;
    unsigned char cidx = p & 0xf;
    return s_box[ridx][cidx];
}

int AES::ReHexReplace(unsigned char p) {
    unsigned char ridx = p >> 4;
    unsigned char cidx = p & 0xf;
    return r_s_box[ridx][cidx];
}

void AES::RowShift(std::vector<unsigned char> &v) {
    // 第0行左移0字节
    // 第一行左移1字节
    unsigned char tmp = v[1];
    v[1] = v[5];
    v[5] = v[9];
    v[9] = v[13];
    v[13] = tmp;

    // 第2行左移2字节
    tmp = v[2];
    v[2] = v[10];
    v[10] = tmp;

    tmp = v[6];
    v[6] = v[14];
    v[14] = tmp;

    // 第3行左移3字节 也可以当作右移1字节
    tmp = v[15];
    v[15] = v[11];
    v[11] = v[7];
    v[7] = v[3];
    v[3] = tmp;

}

void AES::ReRowShift(std::vector<unsigned char> &v) {
    // 第0行左移0字节
    // 第一行左移1字节
    unsigned char tmp = v[3];
    v[3] = v[7];
    v[7] = v[11];
    v[11] = v[15];
    v[15] = tmp;

    // 第2行左移2字节
    tmp = v[2];
    v[2] = v[10];
    v[10] = tmp;

    tmp = v[6];
    v[6] = v[14];
    v[14] = tmp;

    // 第3行左移3字节 也可以当作右移1字节
    tmp = v[13];
    v[13] = v[9];
    v[9] = v[5];
    v[5] = v[1];
    v[1] = tmp;
}

void AES::ColumnMix(std::vector<unsigned char> &v) {
    vector<vector<unsigned char>> mixMatrics = {
        {2, 3, 1, 1},
        {1, 2, 3, 1},
        {1, 1, 2, 3},
        {3, 1, 1, 2}
    };
}

void AES::ReColumnMix(vector<unsigned char> &v) {

}

void AES::multiplyMatrices(vector<vector<unsigned char>>& A, vector<vector<unsigned char>>& B, vector<vector<unsigned char>>& C) {
    // 初始化结果矩阵C
    C.resize(4, vector<unsigned char>(4, 0));

    // 矩阵相乘
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                C[i][j] ^= gfadd(A[i][k], B[k][j]);
            }
        }
    }
}

unsigned char AES::gfadd(unsigned char x, unsigned char y) {
    if (x == 1) return y;

    unsigned char count = x / 2;
    unsigned char mask = y;
    for (int i = 0 ; i < x / 2 ; i++) {
        if (mask & 0x80) {
            mask = (mask << 1) ^ 0x1B;
        } else {
            mask = mask << 1;
        }
    }
    if (x % 2) mask ^= y;
    return mask;
}

