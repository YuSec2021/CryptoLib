//
// Created by YuSec on 2024/12/6.
//

#ifndef MD5_H
#define MD5_H

#include <vector>
#include "../../Tools/Tools.h"
#include "../constants.h"


// 定义四个非线性函数
#define F(x, y, z) (((x) & (y)) | ((~(x) & (z))))
#define G(x, y, z) (((x) & (z)) | ((y) & (~(z))))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) (y ^ (x | ~z))

using namespace std;
using namespace md5;

const int MD5_DIGEST_LENGTH = 16;

typedef uint32_t (*NonLinearFunc)(uint32_t a, uint32_t b, uint32_t c,
        uint32_t d, uint32_t M, uint32_t t, uint32_t shift);

typedef struct _NonLinearFuncStruct {
    NonLinearFunc FF;
    NonLinearFunc GG;
    NonLinearFunc HH;
    NonLinearFunc II;
} NonLinearFuncStruct;

class MD5 {
public:
    // normal Hash
    NonLinearFuncStruct func;
    void init();

    // padding
    void padding(vector<uint8_t> &data);

    // Grouping
    vector<vector<uint32_t>> blockText(vector<uint8_t> &data);

    // Swap Endian
    void encode(vector<uint32_t> &groups);
    void decode(vector<uint32_t> &groups);
    uint32_t swapEndian(uint32_t x);


    // Hash
    void transByRange(vector<uint32_t> &v, vector<uint32_t> &res);
    void transByIterator(vector<uint32_t> &v, uint32_t &A, uint32_t &B, uint32_t &C, uint32_t &D);

    vector<uint32_t> updateIterator(vector<vector<uint32_t>> &groups);
    vector<uint32_t> updateRange(vector<vector<uint32_t>> &groups);

private:
    // Nonlinear function
    uint32_t FF(uint32_t a, uint32_t b, uint32_t c,
        uint32_t d, uint32_t M, uint32_t t, uint32_t shift);
    uint32_t GG(uint32_t a, uint32_t b, uint32_t c,
        uint32_t d, uint32_t M, uint32_t t, uint32_t shift);
    uint32_t HH(uint32_t a, uint32_t b, uint32_t c,
        uint32_t d, uint32_t M, uint32_t t, uint32_t shift);
    uint32_t II(uint32_t a, uint32_t b, uint32_t c,
        uint32_t d, uint32_t M, uint32_t t, uint32_t shift);

public:
    // modified md5
    void padding_modified(vector<uint8_t> &data);
    size_t check(uint8_t a);
};

#endif //MD5_H
