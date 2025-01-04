//
// Created by YuSec on 2024/12/14.
//


#include "gtest/gtest.h"

#include "SHA1.h"


using namespace std;

#ifdef TEST_SHA1

class TestSHA1 : public testing::Test {
protected:
    SHA1 sha1;

    string calculateSHA1(const string& input) {
        vector<uint8_t> plaintext;
        plaintext.insert(plaintext.end(), input.begin(), input.end());
        sha1.init();
        // 填充
        sha1.padding(plaintext);
        // 初始化
        sha1.initializing(plaintext);
        // 散列
        sha1.update();
        stringstream ss;
        for (size_t i = 0; i < sha1.res.size(); i++) {
            ss << hex << setw(8) << setfill('0') << sha1.res[i]; // Pad with zeros for consistent output
        }
        return ss.str();
    }

    void testPadding(const string& input) {
        vector<uint8_t> plaintext;
        plaintext.insert(plaintext.end(), input.begin(), input.end());
        string hexString = Tools::toHexString(plaintext);
        cout << "HexString:" << hexString << endl;

        sha1.padding(plaintext);
        hexString = Tools::toHexString(plaintext);
        cout << "Padding:" << hexString << endl;
    }

};

TEST_F(TestSHA1, testUpdate) {
    const char message[] = {"123456"};
    const char messsage2[] = {"HelloWorld"};
    const char messsage3[] = {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"};
    string expected_hash[] = {"7c4a8d09ca3762af61e59520943dc26494f8941b",
        "db8ac1c259eb89d4a131b253bacfca5f319d54f2",
        "f43b04e4a98aebe3c874514f11a73dbd7d6c150b"};

    ASSERT_EQ(calculateSHA1(message), expected_hash[0]);
    ASSERT_EQ(calculateSHA1(messsage2), expected_hash[1]);
    ASSERT_EQ(calculateSHA1(messsage3), expected_hash[2]);

}

#endif