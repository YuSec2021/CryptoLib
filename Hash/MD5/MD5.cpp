//
// Created by YuSec on 2024/12/6.
//

#include "MD5.h"
#include "../constants.h"
#include <cstdint>


void MD5::init() {
}

size_t MD5::check(uint8_t a) {
    size_t i = 1;
    for (; i < 8; i++) {
        if (a >> i && a >> (i+1) == 0) {
            return i + 1;
        }
    }
    return i;
}

void MD5::padding_modified(vector<uint8_t> &data) {
    uint64_t nBytes = data.size();
    uint32_t nBits = (data.size() - 1) * 8 + this->check(data[0]);
    nBits %= 512;
    size_t paddingBits = 0;
    if (nBits >= 448) {
        paddingBits = 512 - nBits % 448;
    } else {
        paddingBits = 448 - nBits;
    }

    // 拆分两次进行左移，先左移1位，将该为置1
    data = Tools::left_shift(data, 1);
    data[data.size()-1] ^= 0x1;
    paddingBits -= 1;
    data = Tools::left_shift(data, paddingBits);

    // 插入原始信息长度
    vector<uint8_t> MessageSize = Tools::uint64ToVector(nBytes);
    data.insert(data.end(), MessageSize.begin(), MessageSize.end());
}


void MD5::padding(vector<uint8_t> &data) {
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

vector<vector<uint32_t>> MD5::blockText(vector<uint8_t> &data) {
    size_t groupCount = data.size() * 8 / 512;
    vector<vector<uint32_t>> groups(groupCount);
    for (size_t i = 0; i < groupCount; i++) {
        groups[i] = vector<uint32_t>(16, 0);
        for (size_t j = 0; j < 16; j++) {
            for (size_t k = 0; k < 4; k++) {
                groups[i][j] |= (uint32_t)data[j*4+k] << ((3-k)*8);
            }
        }
    }

    return groups;
}

uint32_t MD5::swapEndian(uint32_t x) {
    return ((x >> 24) & 0xff) |
        ((x >> 8) & 0xff00) |
        ((x << 8) & 0xff0000) |
        ((x << 24) & 0xff000000);
}

void MD5::encode(vector<uint32_t> &groups) {
    for (size_t i = 0; i < groups.size(); i++) {
        groups[i] = swapEndian(groups[i]);
    }
}

void MD5::decode(vector<uint32_t> &groups) {
    for (size_t i = 0; i < groups.size(); i++) {
        groups[i] = swapEndian(groups[i]);
    }
}

vector<uint32_t> MD5::updateIterator(vector<vector<uint32_t>> &groups) {
    // 将初始幻数存入
    vector<uint32_t> res = {A, B, C, D};
    // 将输入信息切换成小端序：abcd->0x34333231
    for (size_t i = 0; i < groups.size(); i++) {
        this->encode(groups[i]);
    }

    size_t i = 0;
    while (i < groups.size()) {
        this->transByIterator(groups[i], res[0], res[1], res[2], res[3]);
        i++;
    }
    res[0] += A;
    res[1] += B;
    res[2] += C;
    res[3] += D;

    // Hash后切回大端序并返回
    this->decode(res);
    return res;
}

vector<uint32_t> MD5::updateRange(vector<vector<uint32_t>> &groups) {
    // 将初始幻数存入
    vector<uint32_t> res = {A, B, C, D};

    // 将输入信息切换成小端序：abcd->0x34333231
    for (size_t i = 0; i < groups.size(); i++) {
        this->encode(groups[i]);
    }

    size_t i = 0;
    while (i < groups.size()) {
        this->transByRange(groups[i], res);
        i++;
    }
    res[0] += A;
    res[1] += B;
    res[2] += C;
    res[3] += D;

    // Hash后切回大端序并返回
    this->decode(res);
    return res;
}

void MD5::transByIterator(vector<uint32_t> &v, uint32_t &A, uint32_t &B, uint32_t &C, uint32_t &D) {
    // Round 1
    A = this->FF(A, B, C, D, v[0], 0xd76aa478, 7);
    D = this->FF(D, A, B, C, v[1], 0xe8c7b756, 12);
    C = this->FF(C, D, A, B, v[2], 0x242070db, 17);
    B = this->FF(B, C, D, A, v[3], 0xc1bdceee, 22);
    A = this->FF(A, B, C, D, v[4], 0xf57c0faf, 7);
    D = this->FF(D, A, B, C, v[5], 0x4787c62a, 12);
    C = this->FF(C, D, A, B, v[6], 0xa8304613, 17);
    B = this->FF(B, C, D, A, v[7], 0xfd469501, 22);
    A = this->FF(A, B, C, D, v[8], 0x698098d8, 7);
    D = this->FF(D, A, B, C, v[9], 0x8b44f7af, 12);
    C = this->FF(C, D, A, B, v[10], 0xffff5bb1 , 17);
    B = this->FF(B, C, D, A, v[11], 0x895cd7be, 22);
    A = this->FF(A, B, C, D, v[12], 0x6b901122, 7);
    D = this->FF(D, A, B, C, v[13], 0xfd987193 , 12);
    C = this->FF(C, D, A, B, v[14], 0xa679438e, 17);
    B = this->FF(B, C, D, A, v[15], 0x49b40821 , 22);

    // Round 2
    A = this->GG(A, B, C, D, v[1], 0xf61e2562, 5);
    D = this->GG(D, A, B, C, v[6], 0xc040b340, 9);
    C = this->GG(C, D, A, B, v[11], 0x265e5a51, 14);
    B = this->GG(B, C, D, A, v[0], 0xe9b6c7aa, 20);
    A = this->GG(A, B, C, D, v[5], 0xd62f105d, 5);
    D = this->GG(D, A, B, C, v[10], 0x02441453, 9);
    C = this->GG(C, D, A, B, v[15], 0xd8a1e681, 14);
    B = this->GG(B, C, D, A, v[4], 0xe7d3fbc8, 20);
    A = this->GG(A, B, C, D, v[9], 0x21e1cde6, 5);
    D = this->GG(D, A, B, C, v[14], 0xc33707d6, 9);
    C = this->GG(C, D, A, B, v[3], 0xf4d50d87, 14);
    B = this->GG(B, C, D, A, v[8], 0x455a14ed, 20);
    A = this->GG(A, B, C, D, v[13], 0xa9e3e905, 5);
    D = this->GG(D, A, B, C, v[2], 0xfcefa3f8, 9);
    C = this->GG(C, D, A, B, v[7], 0x676f02d9, 14);
    B = this->GG(B, C, D, A, v[12], 0x8d2a4c8a, 20);

    // Round 3
    A = this->HH(A, B, C, D, v[5], 0xfffa3942, 4);
    D = this->HH(D, A, B, C, v[8], 0x8771f681, 11);
    C = this->HH(C, D, A, B, v[11], 0x6d9d6122, 16);
    B = this->HH(B, C, D, A, v[14], 0xfde5380c, 23);
    A = this->HH(A, B, C, D, v[1], 0xa4beea44, 4);
    D = this->HH(D, A, B, C, v[4], 0x4bdecfa9, 11);
    C = this->HH(C, D, A, B, v[7], 0xf6bb4b60, 16);
    B = this->HH(B, C, D, A, v[10], 0xbebfbc70, 23);
    A = this->HH(A, B, C, D, v[13], 0x289b7ec6, 4);
    D = this->HH(D, A, B, C, v[0], 0xeaa127fa, 11);
    C = this->HH(C, D, A, B, v[3], 0xd4ef3085, 16);
    B = this->HH(B, C, D, A, v[6], 0x04881d05, 23);
    A = this->HH(A, B, C, D, v[9], 0xd9d4d039, 4);
    D = this->HH(D, A, B, C, v[12], 0xe6db99e5, 11);
    C = this->HH(C, D, A, B, v[15], 0x1fa27cf8, 16);
    B = this->HH(B, C, D, A, v[2], 0xc4ac5665, 23);

    // Round 4
    A = this->II(A, B, C, D, v[0], 0xf4292244, 6);
    D = this->II(D, A, B, C, v[7], 0x432aff97, 10);
    C = this->II(C, D, A, B, v[14], 0xab9423a7, 15);
    B = this->II(B, C, D, A, v[5], 0xfc93a039, 21);
    A = this->II(A, B, C, D, v[12], 0x655b59c3, 6);
    D = this->II(D, A, B, C, v[3], 0x8f0ccc92, 10);
    C = this->II(C, D, A, B, v[10], 0xffeff47d, 15);
    B = this->II(B, C, D, A, v[1], 0x85845dd1, 21);
    A = this->II(A, B, C, D, v[8], 0x6fa87e4f, 6);
    D = this->II(D, A, B, C, v[15], 0xfe2ce6e0, 10);
    C = this->II(C, D, A, B, v[6], 0xa3014314, 15);
    B = this->II(B, C, D, A, v[13], 0x4e0811a1, 21);
    A = this->II(A, B, C, D, v[4], 0xf7537e82, 6);
    D = this->II(D, A, B, C, v[11], 0xbd3af235, 10);
    C = this->II(C, D, A, B, v[2], 0x2ad7d2bb, 15);
    B = this->II(B, C, D, A, v[9], 0xeb86d391, 21);
}

void MD5::transByRange(vector<uint32_t> &v, vector<uint32_t> &res) {


    for (size_t i = 0; i < 4; i++) {
        uint32_t* pseudo = pseudoRandom[i];
        uint8_t* shift =  shiftBits[i];
        uint8_t* groupIndex = groupsIndex[i];

        for (size_t k = v.size(); k > 0 ; k--) {
            if (i == 0) {
                res[k % 4] = this->FF(
                    res[k % 4],
                    res[(k + 1) % 4],
                    res[(k + 2) % 4],
                    res[(k + 3) % 4],
                    v[groupIndex[16 - k]],
                    pseudo[16 - k],
                    shift[(16 - k) % 4]);
            }
            else if (i == 1){
                res[k % 4] = this->GG(
                    res[k % 4],
                    res[(k + 1) % 4],
                    res[(k + 2) % 4],
                    res[(k + 3) % 4],
                    v[groupIndex[16 - k]],
                    pseudo[16 - k],
                    shift[(16 - k) % 4]);
            }
            else if (i == 2) {
                res[k % 4] = this->HH(
                    res[k % 4],
                    res[(k + 1) % 4],
                    res[(k + 2) % 4],
                    res[(k + 3) % 4],
                    v[groupIndex[16 - k]],
                    pseudo[16 - k],
                    shift[(16 - k) % 4]);
            }
            else {
                res[k % 4] = this->II(
                    res[k % 4],
                    res[(k + 1) % 4],
                    res[(k + 2) % 4],
                    res[(k + 3) % 4],
                    v[groupIndex[16 - k]],
                    pseudo[16 - k],
                    shift[(16 - k) % 4]);
            }

        }
    }
}

uint32_t MD5::FF(uint32_t a, uint32_t b, uint32_t c,
            uint32_t d, uint32_t M, uint32_t t, uint32_t shift) {
    return b + Tools::rotate_left(a + F(b,c,d) + M + t, shift);
}

uint32_t MD5::GG(uint32_t a, uint32_t b, uint32_t c,
    uint32_t d, uint32_t M, uint32_t t, uint32_t shift) {
    return b + Tools::rotate_left(a + G(b, c, d) + M + t, shift);
}

uint32_t MD5::HH(uint32_t a, uint32_t b, uint32_t c,
    uint32_t d, uint32_t M, uint32_t t, uint32_t shift) {
    return b + Tools::rotate_left(a + H(b, c, d) + M + t, shift);
}

uint32_t MD5::II(uint32_t a, uint32_t b, uint32_t c,
    uint32_t d, uint32_t M, uint32_t t, uint32_t shift) {
    return b + Tools::rotate_left(a + I(b, c, d) + M + t, shift);
}