//
// Created by YuSec on 2024/12/26.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

namespace md5 {
    // 初始化幻数
    const uint32_t A = 0x67452301;
    const uint32_t B = 0xEFCDAB89;
    const uint32_t C = 0x98BADCFE;
    const uint32_t D = 0x10325476;

    // 定义4*4位移矩阵
    inline uint8_t shiftBits[4][4] = {
        {7, 12, 17, 22},
        {5, 9, 14, 20},
        {4, 11, 16, 23},
        {6, 10, 15, 21}
    };

    // 定义4*16伪随机数矩阵
    inline uint32_t pseudoRandom[4][16] = {
        {
            0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
            0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
            0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
            0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821
        },
        {
            0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
            0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
            0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
            0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a
        },
        {
            0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
            0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
            0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
            0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665
        },
        {
            0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
            0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
            0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
            0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
        }
    };

    // 定义
    inline uint8_t groupsIndex[4][16] = {
        {0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF},
        {0x1,0x6,0xB,0,0x5,0xA,0xF,0x4,0x9,0xE,0x3,0x8,0xD,0x2,0x7,0xC},
        {0x5,0x8,0xB,0xE,0x1,0x4,0x7,0xA,0xD,0,0x3,0x6,0x9,0xC,0xF,0x2},
        {0,0x7,0xE,0x5,0xC,0x3,0xA,0x1,0x8,0xF,0x6,0xD,0x4,0xB,0x2,0x9}
    };

}

namespace sha1 {
    const uint32_t A = 0x67452301;
    const uint32_t B = 0xEFCDAB89;
    const uint32_t C = 0x98BADCFE;
    const uint32_t D = 0x10325476;
    const uint32_t E = 0xC3D2E1F0;

    const uint32_t K[4] = {0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6};
}

#endif //CONSTANTS_H
