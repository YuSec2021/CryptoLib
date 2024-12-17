//
// Created by YuSec on 2024/12/6.
//

#ifndef MD5_H
#define MD5_H

#include <vector>
using namespace std;

const int MD5_DIGEST_LENGTH = 16;

const unsigned int A = 0x67452301;
const unsigned int B = 0xEFCDAB89;
const unsigned int C = 0x98BADCFE;
const unsigned int D = 0x10325476;

class MD5 {
public:
    void padding(vector<unsigned char> &data);

    // step 1
    unsigned int F(unsigned int a, unsigned int b, unsigned int c);
    unsigned int G(unsigned int a, unsigned int b, unsigned int c);
    unsigned int H(unsigned int a, unsigned int b, unsigned int c);
    unsigned int I(unsigned int a, unsigned int b, unsigned int c);

    // step 2
    unsigned int FF(unsigned int a, unsigned int b, unsigned int c,
        unsigned int d, unsigned int M, unsigned int s, unsigned int t);
    unsigned int GG(unsigned int a, unsigned int b, unsigned int c,
        unsigned int d, unsigned int M, unsigned int s, unsigned int t);
    unsigned int HH(unsigned int a, unsigned int b, unsigned int c,
        unsigned int d, unsigned int M, unsigned int s, unsigned int t);
    unsigned int II(unsigned int a, unsigned int b, unsigned int c,
        unsigned int d, unsigned int M, unsigned int s, unsigned int t);
};

#endif //MD5_H
