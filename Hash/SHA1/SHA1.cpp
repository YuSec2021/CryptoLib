//
// Created by YuSec on 2024/12/6.
//

#include "SHA1.h"


void SHA1::init() {
    this->res = vector<uint32_t>(5, 0);
}

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
    // uint64_t uBits = 8;
    // while (uBits < 64) {
    //     if (nBits >> uBits) {
    //         uBits += 8;
    //         continue;
    //     }
    //     nBits = nBits << (64-uBits);
    // }

    // 插入原始信息长度
    vector<uint8_t> MessageSize = Tools::uint64ToVector(nBits);
    data.insert(data.end(), MessageSize.begin(), MessageSize.end());
}

void SHA1::initializing(vector<uint8_t> &data) {
    size_t nGroups = data.size() / 64;
    this->groups = vector<vector<uint32_t>>(nGroups, vector<uint32_t>(16, 0));
    for (size_t i = 0; i < nGroups; i++) {
        for (size_t j = 0; j < 16; j++) {
            this->groups[i][j] = *(uint32_t*)&data[i * 16 + j * 4];
        }
    }
}

vector<uint32_t> SHA1::genW(vector<uint32_t> &group) {
    vector<uint32_t> W(80, 0);

    // 填充W[0] - W[15]
    for (size_t t = 0; t < 16; t++) {
        W[t] = Tools::swapEndian(group[t]);
    }

    // 生成 W[16] - W[79]
    for (size_t t = 16; t < 80; t++) {
        W[t] = W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16];
        W[t] = Tools::rotate_left(W[t], 1);
    }

    return W;
}

uint32_t SHA1::F(uint32_t x, uint32_t y, uint32_t z, size_t t) {
    return (t >= 0 && t <= 19) ? ((x & y) | ((~x) & z)) :
           ((t >= 19 && t <= 39) || (t >= 60 && t <= 79)) ? (x ^ y ^ z) :
           ((t >= 40 && t <= 59) ? ((x & y) | (x & z) | (y & z)) : 0);
}

void SHA1::update() {
    this->res = {A, B, C, D, E};
    for (size_t n = 0; n < this->groups.size(); n++) {

        vector<uint32_t> W = this->genW(groups[n]);
        for (size_t t = 0; t < 80; t++) {
            uint32_t tmp =  Tools::rotate_left(res[0], 5);
            tmp += this->F(res[1], res[2], res[3], t);
            tmp += res[4];
            tmp += W[t];
            tmp += K[t / 20];
            // E
            res[4] = res[3];
            // D
            res[3] = res[2];
            // C
            res[2] = Tools::rotate_left(res[1], 30);
            // B
            res[1] = res[0];
            // A
            res[0] = tmp;
        }

        res[0] += A; res[1] += B; res[2] += C; res[3] += D; res[4] += E;
    }
}
