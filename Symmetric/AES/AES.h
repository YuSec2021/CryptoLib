//
// Created by YuSec on 2024/12/6.
//

#ifndef AES_H
#define AES_H

#include "../Tools/Tools.h"
#include "constant.h"



class AES
{
public:
    int hexReplace(std::string hexStr);
    int ReverseHexReplace(std::string byte);
    void RowShift();
    void encrypt();
    void decrypt();
};



#endif //AES_H
