//
// Created by YuSec on 2024/12/14.
//


#include "gtest/gtest.h"

#define MD5_TEST

#include <vector>

#include "MD5.h"

using namespace std;

#ifdef MD5_TEST

TEST(TestMD5, testPadding) {
    char input[] = "Hello world!";
    vector<unsigned char> plaintext;
    plaintext.insert(plaintext.end(), input, input+sizeof(input)-1);
    string hexString = Tools::toHexString(plaintext);
    cout << "Origin hexString: " << hexString << endl;

    // ASSERT_EQ(plaintext.size(), sizeof(input)-1);
    MD5 md5;
    md5.padding(plaintext);
    hexString = Tools::toHexString(plaintext);
    cout << "Padding hexString: " << hexString << endl;

    char input2[] = "123456";
    vector<unsigned char> plaintext2;
    plaintext2.insert(plaintext2.end(), input2, input2+sizeof(input2)-1);
    hexString = Tools::toHexString(plaintext2);
    cout << "Origin hexString: " << hexString << endl;
    md5.padding(plaintext2);
    hexString = Tools::toHexString(plaintext2);
    cout << "Padding hexString: " << hexString << endl;
}

TEST(TestMD5, testBlock) {
    // md5.blockText(plaintext);
}

#endif
