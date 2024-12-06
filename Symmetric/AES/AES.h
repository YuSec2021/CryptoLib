//
// Created by YuSec on 2024/12/6.
//

#ifndef AES_H
#define AES_H

#include "../../Tools/Tools.h"
#include "../constant.h"



class AES
{
public:
    void encrypt();
    void decrypt();

    // encrypt
    int hexReplace(std::string hexStr);
    void RowShift();


    // decrypt
    int ReverseHexReplace(std::string byte);
    void ReverseRowShift();


};



#endif //AES_H
