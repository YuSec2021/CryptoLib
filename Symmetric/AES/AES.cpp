//
// Created by YuSec on 2024/12/6.
//

#include "AES.h"


void AES::keyExpand(vector<uint8_t> &key) {
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

uint32_t AES::T(uint32_t A, uint8_t idx) {
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

uint8_t AES::subHex(uint8_t p) {
    uint8_t ridx = p >> 4;
    uint8_t cidx = p & 0xf;
    return s_box[ridx][cidx];
}

uint8_t AES::reSubHex(uint8_t p) {
    uint8_t ridx = p >> 4;
    uint8_t cidx = p & 0xf;
    return r_s_box[ridx][cidx];
}

void AES::shiftRows(vector<uint8_t> &v) {
    // 第0行左移0字节
    // 第一行左移1字节
    uint8_t tmp = v[1];
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

void AES::reShiftRows(vector<uint8_t> &v) {
    // 第0行左移0字节
    // 第一行左移1字节
    uint8_t tmp = v[3];
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

void AES::enColumnMix(vector<uint8_t> &v) {
    vector<vector<uint8_t>> mixMatrics = {
        {2, 3, 1, 1},
        {1, 2, 3, 1},
        {1, 1, 2, 3},
        {3, 1, 1, 2}
    };
    this->columnMix(mixMatrics, v);
}

void AES::deColumnMix(vector<uint8_t> &v) {
    vector<vector<uint8_t>> remixMatrics = {
        {0xE, 0xB, 0xD, 0x9},
        {0x9, 0xE, 0xB, 0xD},
        {0xD, 0x9, 0xE, 0xB},
        {0xB, 0xD, 0x9, 0xE}
    };
    this->columnMix(remixMatrics, v);
}

void AES::multiplyMatrices(vector<vector<uint8_t>>& A, vector<vector<uint8_t>>& B, vector<vector<uint8_t>>& C) {
    // 初始化结果矩阵C
    C.resize(4, vector<uint8_t>(4, 0));

    // 矩阵相乘
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            for (size_t k = 0; k < 4; k++) {
                C[i][j] ^= GFM(A[i][k], B[k][j]);
            }
        }
    }
}

uint8_t AES::GFM(uint8_t count, uint8_t y) {
    if (count == 1) return y;
    return this->X(count, 0b1000, y)
        ^ this->X(count, 0b100, y)
        ^ this->X(count, 0b10, y)
        ^ this->X(count, 0b1, y);
}

uint8_t AES::X(uint8_t count, uint8_t odd, uint8_t y) {
    uint8_t tmp = 0;
    if (count & odd) {
        tmp ^= this->GFMultiply(log2(odd), y);
    }
    return tmp;
}

uint8_t AES::GFMultiply(uint8_t count, uint8_t y) {
    uint8_t mask = y;
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

void AES::columnMix(vector<vector<uint8_t>> matrics, vector<uint8_t> &v) {
    vector<vector<uint8_t>> res;
    vector<vector<uint8_t>> v2 = Tools::convertToVectorOfVectors(v);
    this->multiplyMatrices(matrics, v2, res);
    for (size_t i = 0; i < 16; i++) {
        v[i] = res[i % 4][i / 4];
    }
}

void AES::rotXor(vector<uint8_t> &v, uint8_t i){
    vector<uint8_t> tmp;
    for (size_t j = 0; j < 4; j++) {
        for (size_t k = 0; k < 4; k++) {
            tmp.push_back(this->w[4*i + j] >> ((3-k) * 8));
        }
    }

    for (size_t idx = 0; idx < 16; idx++) {
        v[idx] ^= tmp[idx];
    }
}

void AES::encrypt(vector<uint8_t> &plaintext, vector<uint8_t> &key, int MODE) {
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

void AES::decrypt(vector<uint8_t> &ciphertext, vector<uint8_t> &key, int MODE) {
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