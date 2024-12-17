//
// Created by YuSec on 2024/12/14.
//


#include "gtest/gtest.h"

#define MD5_TEST

#include <vector>

#include "MD5.h"

using namespace std;

TEST(TestMD5, testPadding) {
    char input[] = "Hello world!";
    vector<unsigned char> plaintext;
    plaintext.insert(plaintext.end(), input, input+sizeof(input)-1);
    ASSERT_EQ(plaintext.size(), sizeof(input)-1);

    MD5 md5;
    md5.padding(plaintext);
}

