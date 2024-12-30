//
// Created by YuSec on 2024/12/6.
//

#include "SHA1.h"

void SHA1::padding(vector<uint8_t> &data) {
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

    // 确认有效信息位
    uint64_t uBits = 8;
    while (uBits < 64) {
        if (nBits >> uBits) {
            uBits += 8;
            continue;
        }
        nBits = nBits << (64-uBits);
    }

    // 插入原始信息长度
    vector<uint8_t> MessageSize = Tools::uint64ToVector(nBits);
    data.insert(data.end(), MessageSize.begin(), MessageSize.end());

}

void SHA1::initialize(vector<uint8_t> &data) {
    size_t nGroups = data.size() / 64;

    vector<vector<uint32_t>> groups(nGroups, vector<uint32_t>(16, 0));
    for (size_t i = 0; i < nGroups; i++) {
        for (size_t j = 0; j < 16; j++) {
            groups[i][j] = *(uint32_t*)&data[i * 16 + j * 4];
        }
    }
}

void SHA1::genW(vector<uint32_t> &group) {
    vector<uint32_t> W(80, 0);

}

void SHA1::update() {

}

