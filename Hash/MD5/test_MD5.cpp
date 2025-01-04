//
// Created by YuSec on 2024/12/14.
//


#include "gtest/gtest.h"
#include "gtest/gtest-spi.h"

#include <vector>

#include "MD5.h"


using namespace std;
//#define MD5_TEST
#ifdef MD5_TEST

class TestMD5 : public ::testing::Test {
protected:
    MD5 md5; // Instance of MD5 class for each test

    string calculateMD5(const string& input, int choice) {
        vector<uint8_t> plaintext;
        plaintext.insert(plaintext.end(), input.begin(), input.end());

        md5.padding(plaintext);
        vector<vector<uint32_t>> groups = md5.blockText(plaintext);
        vector<uint32_t> res;
        if (choice == 1) {
            res = md5.updateRange(groups);
        } else {
            res = md5.updateIterator(groups);
        }
        stringstream ss;
        for (size_t i = 0; i < res.size(); i++) {
            ss << hex << setw(8) << setfill('0') << res[i]; // Pad with zeros for consistent output
        }
        return ss.str();
    }

};


TEST_F(TestMD5, testUpdateByRange) {
    const char input[] = "123456";
    string res = calculateMD5(input, 1);
    string expected = "e10adc3949ba59abbe56e057f20f883e";
    ASSERT_EQ(expected, res);
}

TEST_F(TestMD5, testUpdateByIterator) {
    const char input[] = "123456";
    string res = calculateMD5(input, 2);
    string expected = "e10adc3949ba59abbe56e057f20f883e";
    ASSERT_EQ(expected, res);
}

TEST_F(TestMD5, testMultiGroup) {
    const char input[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string res = calculateMD5(input, 1);
    string expect_hash = "76658de2ac7d406f93dfbe8bb6d9f549";
    ASSERT_EQ(res, expect_hash);
}

#endif
