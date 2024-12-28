//
// Created by YuSec on 2024/12/6.
//

#ifndef SHA1_H
#define SHA1_H

#include <vector>
#include "../../Tools/Tools.h"

using namespace std;

class SHA1 {
    void padding();

    void update();
};



#endif //SHA1_H
