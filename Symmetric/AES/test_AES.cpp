//
// Created by YuSec on 2024/12/14.
//

#include "AES.h"
#include "gtest/gtest.h"


#ifdef AES_TEST
TEST(TestAES, TestColumnMix) {
    cout << "Testing Column Mix" << endl;
    AES aes;

    vector<uint8_t> data = {
        0xC9, 0x7A, 0x63, 0xB0,
        0xE5, 0xF2, 0x9C, 0xA7,
        0xFD, 0x78, 0x26, 0x82,
        0x2B, 0x6E, 0x67, 0xE5
    };

    aes.enColumnMix(data);

    vector<vector<uint8_t>> remixMatrics = {
        {0xE, 0xB, 0xD, 0x9},
        {0x9, 0xE, 0xB, 0xD},
        {0xD, 0x9, 0xE, 0xB},
        {0xB, 0xD, 0x9, 0xE}
    };

    vector<vector<uint8_t>> res = Tools::convertToVectorOfVectors(data);
    vector<vector<uint8_t>> res2;
    aes.multiplyMatrices(remixMatrics, res, res2);
    system("pause");
}

TEST(TestAES, TestEncAndDec) {
    AES aes;

    char a[] = "abcdefghijklmnop";
    // vector<uint8_t> plaintext;
    // for (int i = 0; i < sizeof(a); i++) {
    //     uint8_t tmp = stoi(Tools::charToHex(a[i]), 0, 16);
    //     plaintext.push_back(tmp);
    // }

    vector<uint8_t> plaintext = {
        0x61, 0x62, 0x63, 0x64,
        0x65, 0x66, 0x67, 0x68,
        0x69, 0x6A, 0x6B, 0x6C,
        0x6D, 0x6E, 0x6F, 0x70
    };

    vector<uint8_t> key = {
        0x61, 0x62, 0x63, 0x64,
        0x65, 0x66, 0x67, 0x68,
        0x69, 0x6A, 0x6B, 0x6C,
        0x6D, 0x6E, 0x6F, 0x70
    };


    //aes.keyExpand(key);

    aes.encrypt(plaintext, key, AES128);
    string resr = Tools::toHexString(plaintext);
    cout << "Encrypt Result: " << resr << endl;

    vector<uint8_t> ciphertext = {
        0xa9, 0x13, 0x29, 0xaf,
        0x99, 0xa7, 0x8d, 0x02,
        0xae, 0xc1, 0x7c, 0x50,
        0x77, 0x57, 0xaa, 0xef
    };

    aes.decrypt(ciphertext, key, AES128);
    resr = Tools::toHexString(ciphertext);
    cout << "Decrypt Result: " << resr << endl;
}

TEST(TestAES, TestGFMultiply) {
    AES aes;
    printf("%02X\n", aes.GFM(0x2, 0xC9)^aes.GFM(0x3, 0x7A)^aes.GFM(1, 0x63)^aes.GFM(1, 0xb0));

    printf("%02X\n", aes.GFM(0xe, 0xd4)^aes.GFM(0xb, 0x28)^aes.GFM(0xd, 0xbe)^aes.GFM(0x9, 0x22));
}

#endif