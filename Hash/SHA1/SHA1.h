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
    void padding(vector<uint8_t> &data);
    void initialize(vector<uint8_t> &data);

    void genW(vector<uint32_t> &data);
    uint32_t f(uint32_t b, uint32_t c, uint32_t d, size_t t);
    void update();
};



#endif //SHA1_H
