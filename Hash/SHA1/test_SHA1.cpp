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
    sha1.initializing(plaintext);

}

TEST(TestSHA1, testUpdate) {
    char message[] = "123456";
    vector<uint8_t> plaintext;
    plaintext.insert(plaintext.end(), message, message+sizeof(message)-1);



    SHA1 sha1;
    sha1.init();
    // 填充
    sha1.padding(plaintext);
    // 初始化
    sha1.initializing(plaintext);
    // 散列
    sha1.update();
    cout << "sha1(" << message << ")=" ;
    for (size_t i = 0; i < sha1._res.size(); i++) {
        cout << hex << sha1._res[i];
    }

    cout << endl;

    char message2[] = "HelloWorld";
    plaintext.clear();
    plaintext.insert(plaintext.end(), message2, message2+sizeof(message2)-1);
    sha1.padding(plaintext);
    sha1.initializing(plaintext);
    sha1.update();

    cout << "sha1(" << message2 << ")=" ;
    for (size_t i = 0; i < sha1.res.size(); i++) {
        cout << hex << sha1.res[i];
    }

}

#endif