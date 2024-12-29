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

#endif