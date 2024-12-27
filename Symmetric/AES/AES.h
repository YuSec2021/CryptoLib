//
// Created by YuSec on 2024/12/6.
//

#ifndef AES_H
#define AES_H

#include "../../Tools/Tools.h"
#include "../constant.h"
#include <vector>
#include <cmath>

using namespace std;

class AES
{
public:
    uint32_t w[44] = {0};

    void encrypt(vector<uint8_t> &plaintext, vector<uint8_t> &key, int MODE);
    void decrypt(vector<uint8_t> &ciphertext, vector<uint8_t> &key, int MODE);

    // Step 0
    void keyExpand(vector<uint8_t> &key);
    uint32_t T(uint32_t A, uint8_t idx);

    // Step 1
    uint8_t subHex(uint8_t p);
    uint8_t reSubHex(uint8_t p);

    // Step 2
    void shiftRows(vector<uint8_t> &v);
    void reShiftRows(vector<uint8_t> &v);

    // Step 3
    void multiplyMatrices(
        vector<vector<uint8_t>>& A,
        vector<vector<uint8_t>>& B,
        vector<vector<uint8_t>>& C);
    uint8_t GFM(uint8_t count, uint8_t y);
    uint8_t X(uint8_t count, uint8_t odd, uint8_t y);
    uint8_t GFMultiply(uint8_t x, uint8_t y);


    void enColumnMix(vector<uint8_t> &v);
    void deColumnMix(vector<uint8_t> &v);
    void columnMix(vector<vector<uint8_t>> matrics, vector<uint8_t> &v);

    // Step 4
    void rotXor(vector<uint8_t> &v, uint8_t i);
};

#endif //AES_H
