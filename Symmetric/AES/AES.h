//
// Created by YuSec on 2024/12/6.
//

#ifndef AES_H
#define AES_H

#include "../../Tools/Tools.h"
#include "../constant.h"
#include <vector>

using namespace std;

class AES
{
public:
    vector<int> plaintext;

    void encrypt();
    void decrypt();

    // encrypt
    int hexReplace(unsigned char p);
    void RowShift(vector<unsigned char> &v);
    void ColumnMix(vector<unsigned char> &v);

    // decrypt
    int ReHexReplace(unsigned char p);
    void ReRowShift(vector<unsigned char> &v);
    void ReColumnMix(vector<unsigned char> &v);
    void multiplyMatrices(
        vector<vector<unsigned char>>& A,
        vector<vector<unsigned char>>& B,
        vector<vector<unsigned char>>& C);
    unsigned char gfadd(unsigned char x, unsigned char y);
};



#endif //AES_H
