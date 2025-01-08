//
// Created by YuSec on 2024/12/6.
//

#include "SHA256.h"

#include <cstdint>


void SHA256::init() {
    // initial res
    res = vector<uint32_t>(8, 0);
    for (size_t t = 0; t < 8; t++) {
        res[t] = H[t];
    }
}

void SHA256::clear() {
    groups.clear();
    res.clear();
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

vector<uint32_t> SHA256::genW(vector<uint32_t> &group) {
    vector<uint32_t> W(64, 0);
    // W[0]-W[15]
    for (size_t t = 0; t < 16; t++) {
        W[t] = Tools::swapEndian(group[t]);
    }

    // W[16]-W[63]
    for (size_t t = 16; t < 64; t++) {
        W[t] = SHA256::Sigma4(W[t-2]) + W[t-7] + SHA256::Sigma3(W[t-15]) + W[t-16];
    }

    return W;
}


void SHA256::update() {
    for (size_t i = 0; i < groups.size(); i++) {
        // 中间链接变量
        uint32_t H0 = res[0];
        uint32_t H1 = res[1];
        uint32_t H2 = res[2];
        uint32_t H3 = res[3];
        uint32_t H4 = res[4];
        uint32_t H5 = res[5];
        uint32_t H6 = res[6];
        uint32_t H7 = res[7];
        vector<uint32_t> W = genW(this->groups[i]);
        for (size_t t = 0; t < 64; t++) {
            uint32_t tmp = Sigma2(H4) + H7 + Ch(H4, H5, H6) + W[t] + K[t];
            uint32_t tmp2 = Maj(H0, H1, H2) + Sigma1(H0);
            H7 = H6;
            H6 = H5;
            H5 = H4;
            H4 = H3 + tmp;
            H3 = H2;
            H2 = H1;
            H1 = H0;
            H0 = tmp + tmp2;
        }
        // 一组循环结果加回res，作为下一组的初始链接变量
        res[0] += H0;
        res[1] += H1;
        res[2] += H2;
        res[3] += H3;
        res[4] += H4;
        res[5] += H5;
        res[6] += H6;
        res[7] += H7;
    }

}


void SHA256::finalize() {

}

uint32_t SHA256::Sigma1(uint32_t x) {
    return Tools::rotate_right(x, 2) ^ Tools::rotate_right(x, 13) ^ Tools::rotate_right(x, 22);
}

uint32_t SHA256::Sigma2(uint32_t x) {
    return Tools::rotate_right(x, 6) ^ Tools::rotate_right(x, 11) ^ Tools::rotate_right(x, 25);
}

uint32_t SHA256::Sigma3(uint32_t x) {
    return Tools::rotate_right(x, 7) ^ Tools::rotate_right(x, 18) ^ (x >> 3);
}

uint32_t SHA256::Sigma4(uint32_t x) {
    return Tools::rotate_right(x, 17) ^ Tools::rotate_right(x, 19) ^ (x >> 10);
}
