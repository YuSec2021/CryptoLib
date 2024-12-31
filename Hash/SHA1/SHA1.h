//
// Created by YuSec on 2024/12/6.
//

#ifndef SHA1_H
#define SHA1_H

#include <vector>
#include "../../Tools/Tools.h"
#include "../constants.h"

using namespace sha1;
using namespace std;

class SHA1 {
public:
    vector<vector<uint32_t>> groups;
    vector<uint32_t> res;

    // step 0
    void init();

    // Step 1
    void padding(vector<uint8_t> &data);

    // Step 2
    void initializing(vector<uint8_t> &data);
    vector<uint32_t> genW(vector<uint32_t> &data);
    uint32_t F(uint32_t x, uint32_t y, uint32_t z, size_t t);

    // Step 3
    void rotFunc(vector<uint32_t> &res, size_t t);
    void update();
};

#endif //SHA1_H
