//
// Created by YuSec on 2024/12/14.
//


#include "SHA256.h"
#include "gtest/gtest.h"


using namespace std;
class TestSHA256 : public ::testing::Test {
protected:
    SHA256 sha256;
    string calculateSHA256(const string &message) {
        vector<uint8_t> plaintext;
        plaintext.insert(plaintext.end(), message.begin(), message.end());
        // 初始化
        sha256.init();
        // 填充
        sha256.padding(plaintext);
        // 分组
        sha256.grouping(plaintext);
        // 散列
        sha256.update();
        stringstream ss;
        for (size_t i = 0; i < sha256.res.size(); i++) {
            ss << hex << setw(8) << setfill('0') << sha256.res[i]; // Pad with zeros for consistent output
        }
        sha256.clear();
        return ss.str();
    }

};

TEST_F(TestSHA256, testSHA256) {
    const char input[3][100] = {
        "123456",
        "HelloWorld",
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",
    };
    const string expected_hash[] = {
        "8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92",
        "872e4e50ce9990d8b041330c47c9ddd11bec6b503ae9386a99da8584e9bb12c4",
        "540363d1071a002997290cd8f4a2bdf3acd0355ffad3b3f25f52aad6ebad936a"
    };
    for (int i = 0; i < 3; i++) {
        ASSERT_EQ(calculateSHA256(input[i]), expected_hash[i]);
    }
}