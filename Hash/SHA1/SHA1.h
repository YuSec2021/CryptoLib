//
// Created by YuSec on 2024/12/6.
//

#ifndef SHA1_H
#define SHA1_H

#include <vector>
#include "../../Tools/Tools.h"

using namespace std;

class SHA1 {
public:
    void padding(vector<uint8_t> &data);

    void update();
};



#endif //SHA1_H
