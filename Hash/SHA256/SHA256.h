//
// Created by YuSec on 2024/12/6.
//

#ifndef SHA256_H
#define SHA256_H
#include <cstdint>
#include <vector>

#include "../constants.h"
#include "../../Tools/Tools.h"

using namespace std;
using namespace sha256;

#define Ch(x, y, z) ((x & y) ^ (~x & z))
#define Maj(x, y, z) ((x & y) ^ (x & z) ^ (y & z))

class SHA256 {
public:
    vector<vector<uint32_t>> groups;
    vector<uint32_t> res;

    void clear();
    void init();
    void padding(vector<uint8_t> &data);
    void grouping(vector<uint8_t> &data);
    void update();
    vector<uint32_t> genW(vector<uint32_t> &group);
    void finalize();

    // 非线性函数
    uint32_t Sigma1(uint32_t x);
    uint32_t Sigma2(uint32_t x);
    uint32_t Sigma3(uint32_t x);
    uint32_t Sigma4(uint32_t x);

};



#endif //SHA256_H
