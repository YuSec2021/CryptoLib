//
// Created by YuSec on 2024/12/6.
//

#ifndef AES_H
#define AES_H

#include "../../Tools/Tools.h"
#include "../constant.h"
#include <vector>


class AES
{
public:
    std::vector<int> plaintext;

    void encrypt();
    void decrypt();

    // encrypt
    int hexReplace(unsigned char p);
    void RowShift();


    // decrypt
    int ReverseHexReplace(unsigned char p);
    void ReverseRowShift();


};



#endif //AES_H
