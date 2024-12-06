//
// Created by YuSec on 2024/12/6.
//

#include "AES.h"

void AES::encrypt() {
    unsigned char ret = stoi(hexStr, 0, 16);
}

void AES::decrypt() {

}


int AES::hexReplace(unsigned char p) {
    unsigned char ridx = p >> 4;
    unsigned char cidx = p & 0xf;
    return s_box[ridx][cidx];
}

int AES::ReverseHexReplace(unsigned char p) {
    unsigned char ridx = p >> 4;
    unsigned char cidx = p & 0xf;
    return r_s_box[ridx][cidx];
}

void AES::RowShift() {

}

void AES::ReverseRowShift() {

}
