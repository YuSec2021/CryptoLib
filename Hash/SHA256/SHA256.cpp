//
// Created by YuSec on 2024/12/6.
//

#include "SHA256.h"

#include <cstdint>


void SHA256::init() {

}

void SHA256::padding(vector<uint8_t> &data) {
    uint64_t nBits = data.size() * 8;
    size_t paddingBits = 0;
    if (nBits % 512 >= 448) {
        paddingBits = 512 - nBits % 512 % 448;
    } else {
        paddingBits = 448 - nBits;
    }

    // 拆分两次进行左移，先左移1位，将该为置1
    data = Tools::left_shift(data, 1);
    data[data.size()-1] ^= 0x1;
    paddingBits -= 1;
    data = Tools::left_shift(data, paddingBits);

    // 插入原始信息长度
    vector<uint8_t> MessageSize = Tools::uint64ToVector(nBits);
    data.insert(data.end(), MessageSize.begin(), MessageSize.end());
}


void SHA256::grouping(vector<uint8_t> &data) {
    size_t nGroups = data.size() / 64;
    this->groups = vector<vector<uint32_t>>(nGroups, vector<uint32_t>(16, 0));
    for (size_t i = 0; i < nGroups; i++) {
        for (size_t j = 0; j < 16; j++) {
            this->groups[i][j] = *(uint32_t*)&data[i * 64 + j * 4];
        }
    }

}

void SHA256::update() {
    vector<uint32_t> res;



}


void SHA256::finalize() {

}
