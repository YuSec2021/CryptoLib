//
// Created by YuSec on 2024/12/6.
//

#include "AES.h"


void AES::keyExpand(vector<unsigned char> &key) {
    for (size_t i = 0; i < 4; i++) {
        this->w[i] = key[4*i] << 24 | key[4*i + 1] << 16 | key[4*i + 2] << 8 | key[4*i + 3];
    }

    for (size_t i = 4, j = 0; i < 44 ; i++) {
        if (i % 4 == 0) {
            this->w[i] = this->w[i - 4] ^ T(this->w[i - 1], j++);
        } else {
            this->w[i] = this->w[i - 4] ^ this->w[i - 1];
        }
    }
}

unsigned int AES::T(unsigned int A, unsigned char idx) {
    // 移位操作
    int tmp = A >> 24;
    A = A << 8 | tmp;

    // Sbox
    A = subHex(A >> 24) << 24 |
        subHex(A >> 16) << 16 |
        subHex(A >> 8) << 8 |
        subHex(A);

    return A ^ Rcon[idx];
}

unsigned char AES::subHex(unsigned char p) {
    unsigned char ridx = p >> 4;
    unsigned char cidx = p & 0xf;
    return s_box[ridx][cidx];
}

unsigned char AES::reSubHex(unsigned char p) {
    unsigned char ridx = p >> 4;
    unsigned char cidx = p & 0xf;
    return r_s_box[ridx][cidx];
}

void AES::shiftRows(vector<unsigned char> &v) {
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

void AES::reShiftRows(vector<unsigned char> &v) {
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

void AES::enColumnMix(vector<unsigned char> &v) {
    vector<vector<unsigned char>> mixMatrics = {
        {2, 3, 1, 1},
        {1, 2, 3, 1},
        {1, 1, 2, 3},
        {3, 1, 1, 2}
    };
    this->columnMix(mixMatrics, v);
}

void AES::deColumnMix(vector<unsigned char> &v) {
    vector<vector<unsigned char>> remixMatrics = {
        {0xE, 0xB, 0xD, 0x9},
        {0x9, 0xE, 0xB, 0xD},
        {0xD, 0x9, 0xE, 0xB},
        {0xB, 0xD, 0x9, 0xE}
    };
    this->columnMix(remixMatrics, v);
}

void AES::multiplyMatrices(vector<vector<unsigned char>>& A, vector<vector<unsigned char>>& B, vector<vector<unsigned char>>& C) {
    // 初始化结果矩阵C
    C.resize(4, vector<unsigned char>(4, 0));

    // 矩阵相乘
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            for (size_t k = 0; k < 4; k++) {
                C[i][j] ^= GFM(A[i][k], B[k][j]);
            }
        }
    }
}

unsigned char AES::GFM(unsigned char count, unsigned char y) {
    if (count == 1) return y;
    return this->X(count, 0b1000, y)
        ^ this->X(count, 0b100, y)
        ^ this->X(count, 0b10, y)
        ^ this->X(count, 0b1, y);
}

unsigned char AES::X(unsigned char count, unsigned char odd, unsigned char y) {
    unsigned char tmp = 0;
    if (count & odd) {
        tmp ^= this->GFMultiply(log2(odd), y);
    }
    return tmp;
}

unsigned char AES::GFMultiply(unsigned char count, unsigned char y) {
    unsigned char mask = y;
    size_t i = 0;
    while (i < count) {
        if (mask & 0x80) {
            mask = mask << 1 ^ 0x1b;
        } else {
            mask = mask << 1;
        }
        i++;
    }
    return mask;
}

void AES::columnMix(vector<vector<unsigned char>> matrics, vector<unsigned char> &v) {
    vector<vector<unsigned char>> res;
    vector<vector<unsigned char>> v2 = Tools::convertToVectorOfVectors(v);
    this->multiplyMatrices(matrics, v2, res);
    for (size_t i = 0; i < 16; i++) {
        v[i] = res[i % 4][i / 4];
    }
}

void AES::rotXor(vector<unsigned char> &v, unsigned char i){
    vector<unsigned char> tmp;
    for (size_t j = 0; j < 4; j++) {
        for (size_t k = 0; k < 4; k++) {
            tmp.push_back(this->w[4*i + j] >> ((3-k) * 8));
        }
    }

    for (size_t idx = 0; idx < 16; idx++) {
        v[idx] ^= tmp[idx];
    }
}

void AES::encrypt(vector<unsigned char> &plaintext, vector<unsigned char> &key, int MODE) {
    switch (MODE) {
        case AES128: {
            this->keyExpand(key);
            this->rotXor(plaintext, 0);
            for (int i = 1; i < 10; i++) {
                // byte replace
                for (int j = 0; j < 16; j++) {
                    plaintext[j] = this->subHex(plaintext[j]);
                }
                // line rotate
                this->shiftRows(plaintext);
                // Column Mix
                this->enColumnMix(plaintext);
                // Rotate
                this->rotXor(plaintext, i);
            }
            // byte replace
            for (int j = 0; j < 16; j++) {
                plaintext[j] = this->subHex(plaintext[j]);
            }
            // line rotate
            this->shiftRows(plaintext);
            // Rotate
            this->rotXor(plaintext, 10);
            break;
        }
        case AES192: {
            this->keyExpand(key);
            break;
        }
        case AES256: {
            this->keyExpand(key);
            break;
        }
    }
}

void AES::decrypt(vector<unsigned char> &ciphertext, vector<unsigned char> &key, int MODE) {
    switch (MODE) {
        case AES128: {
            this->keyExpand(key);
            this->rotXor(ciphertext, 10);
            for (int i = 9; i > 0; i--) {
                // line rotate
                this->reShiftRows(ciphertext);
                // byte replace
                for (int j = 0; j < 16; j++) {
                    ciphertext[j] = this->reSubHex(ciphertext[j]);
                }
                // Rotate
                this->rotXor(ciphertext, i);
                // Column Mix
                this->deColumnMix(ciphertext);
            }
            // line rotate
            this->reShiftRows(ciphertext);
            // byte replace
            for (int j = 0; j < 16; j++) {
                ciphertext[j] = this->reSubHex(ciphertext[j]);
            }
            // Rotate
            this->rotXor(ciphertext, 0);
            break;
        }
        case AES192: {
            this->keyExpand(key);
            break;
        }
        case AES256: {
            this->keyExpand(key);
            break;
        }
    }
}