//
// Created by YuSec on 2024/12/6.
//

#include "AES.h"

void AES::encrypt() {

}

void AES::decrypt() {

}


int AES::hexReplace(std::string hexStr) {
    unsigned char ret = stoi(hexStr, 0, 16);
    unsigned char ridx = ret >> 4;
    unsigned char cidx = ret & 0xf;
    return s_box[ridx][cidx];
}

int AES::ReverseHexReplace(std::string hexStr) {
    unsigned char ret = stoi(hexStr, 0, 16);
    unsigned char ridx = ret >> 4;
    unsigned char cidx = ret & 0xf;
    return r_s_box[ridx][cidx];
}

void AES::RowShift() {

}

void AES::ReverseRowShift() {

}
