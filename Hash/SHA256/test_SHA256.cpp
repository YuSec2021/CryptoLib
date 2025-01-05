//
// Created by YuSec on 2024/12/14.
//


#include "SHA256.h"
#include "gtest/gtest.h"


using namespace std;
class TestSHA256 : public ::testing::Test {
protected:
    SHA256 sha256;


};

TEST_F(TestSHA256, testinit) {
    char input[] = "HelloWorld";
    vector<uint8_t> plaintext;
    plaintext.insert(plaintext.end(), input, input+sizeof(input)-1);

    string originString = Tools::toHexString(plaintext);
    cout << originString << endl;
    sha256.init();
    sha256.padding(plaintext);
    sha256.grouping(plaintext);

    string hexString = Tools::toHexString(plaintext);
    cout << hexString << endl;
}