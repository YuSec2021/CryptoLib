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
    unsigned int w[44] = {0};

    void encrypt(vector<unsigned char> &plaintext, vector<unsigned char> &key, int MODE);
    void decrypt(vector<unsigned char> &ciphertext, vector<unsigned char> &key, int MODE);

    // Step 0
    void keyExpand(vector<unsigned char> &key);
    unsigned int T(unsigned int A, unsigned char idx);

    // Step 1
    unsigned char subHex(unsigned char p);
    unsigned char reSubHex(unsigned char p);

    // Step 2
    void shiftRows(vector<unsigned char> &v);
    void reShiftRows(vector<unsigned char> &v);

    // Step 3
    void multiplyMatrices(
        vector<vector<unsigned char>>& A,
        vector<vector<unsigned char>>& B,
        vector<vector<unsigned char>>& C);
    unsigned char GFM(unsigned char count, unsigned char y);
    unsigned char X(unsigned char count, unsigned char odd, unsigned char y);
    unsigned char GFMultiply(unsigned char x, unsigned char y);


    void enColumnMix(vector<unsigned char> &v);
    void deColumnMix(vector<unsigned char> &v);
    void columnMix(vector<vector<unsigned char>> matrics, vector<unsigned char> &v);

    // Step 4
    void rotXor(vector<unsigned char> &v, unsigned char i);




};

#endif //AES_H
