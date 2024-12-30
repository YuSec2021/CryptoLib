//
// Created by YuSec on 2024/12/14.
//


#include "gtest/gtest.h"

#include "SHA1.h"


#define TEST_SHA1

using namespace std;

#ifdef TEST_SHA1
TEST(TestSHA1, testPadding) {
    char message[] = "HelloWorld";
    vector<uint8_t> plaintext;
    plaintext.insert(plaintext.end(), message, message+sizeof(message)-1);
    string hexString = Tools::toHexString(plaintext);
    cout << "HexString:" << hexString << endl;

    SHA1 sha1;
    sha1.padding(plaintext);
    hexString = Tools::toHexString(plaintext);
    cout << "Padding:" << hexString << endl;
}

TEST(TestSHA1, testInitialing) {
    char message[] = "HelloWorld";
    vector<uint8_t> plaintext;
    plaintext.insert(plaintext.end(), message, message+sizeof(message)-1);

    // 填充
    SHA1 sha1;
    sha1.padding(plaintext);
    string hexString = Tools::toHexString(plaintext);
    cout << "Padding:" << hexString << endl;

    // 初始化
    sha1.initialize(plaintext);

}

TEST(TestSHA1, testUpdate) {
    char message[] = "HelloWorld";
    vector<uint8_t> plaintext;
    plaintext.insert(plaintext.end(), message, message+sizeof(message)-1);
}

#endif