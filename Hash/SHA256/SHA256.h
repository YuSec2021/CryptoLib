//
// Created by YuSec on 2024/12/6.
//

#ifndef SHA256_H
#define SHA256_H
#include <cstdint>
#include <vector>
#include "../../Tools/Tools.h"
using namespace std;

class SHA256 {
public:
    vector<vector<uint32_t>> groups;

    void init();
    void padding(vector<uint8_t> &data);
    void grouping(vector<uint8_t> &data);
    void update();
    void finalize();
};



#endif //SHA256_H
