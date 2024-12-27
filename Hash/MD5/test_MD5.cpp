//
// Created by YuSec on 2024/12/14.
//


#include "gtest/gtest.h"
#include "gtest/gtest-spi.h"

#include <vector>

#include "MD5.h"

#define MD5_TEST

using namespace std;

#ifdef MD5_TEST

TEST(TestMD5, DISABLED_testPadding) {
    char input[] = "HelloWorld";
    vector<uint8_t> plaintext;
    plaintext.insert(plaintext.end(), input, input+sizeof(input)-1);
    string hexString = Tools::toHexString(plaintext);
    cout << "Origin hexString: " << hexString << endl;

    // ASSERT_EQ(plaintext.size(), sizeof(input)-1);
    MD5 md5;
    md5.padding(plaintext);
    hexString = Tools::toHexString(plaintext);
    cout << "Padding hexString: " << hexString << endl;

    char input2[] = "123456";
    vector<uint8_t> plaintext2;
    plaintext2.insert(plaintext2.end(), input2, input2+sizeof(input2)-1);
    hexString = Tools::toHexString(plaintext2);
    cout << "Origin hexString: " << hexString << endl;
    md5.padding(plaintext2);
    hexString = Tools::toHexString(plaintext2);
    cout << "Padding hexString: " << hexString << endl;

    cout << hex << md5.swapEndian(0x12345678);
}

TEST(TestMD5, DISABLED_testBlock) {
    char input[] = "HelloWorld";
    vector<uint8_t> plaintext;
    plaintext.insert(plaintext.end(), input, input+sizeof(input)-1);

    MD5 md5;
    md5.padding(plaintext);
    string hexString = Tools::toHexString(plaintext);
    cout << "Padding hexString: " << hexString << endl;
    vector<vector<uint32_t>> groups = md5.blockText(plaintext);
}

TEST(TestMD5, testUpdateByIterator) {
    char input[] = "HelloWorld";
    // testing::StopWatch sw;
    vector<uint8_t> plaintext;
    plaintext.insert(plaintext.end(), input, input+sizeof(input)-1);

    // 填充
    MD5 md5;
    md5.padding(plaintext);
    // 分组
    vector<vector<uint32_t>> groups = md5.blockText(plaintext);
    // sw.start();
    // Hash
    vector<uint32_t> res = md5.updateIterator(groups);
    // sw.stop();

    // double elapsed_time = sw.ElapsedMillis();
    // cout << "(Iterator)Elapsed Time: " << elapsed_time << " ms" << endl;
    // 输出
    cout << "md5(" << input << ")=";
    for (size_t i = 0; i < res.size(); i++) {
        cout << hex << res[i];
    }
}


TEST(TestMD5, testUpdateByRange) {
    char input[] = "HelloWorld";
    // testing::StopWatch sw;
    // 初始化
    vector<uint8_t> plaintext;
    plaintext.insert(plaintext.end(), input, input+sizeof(input)-1);

    // 填充
    MD5 md5;
    md5.padding(plaintext);
    // 分组
    vector<vector<uint32_t>> groups = md5.blockText(plaintext);
    // sw.start();
    // Hash
    vector<uint32_t> res = md5.updateRange(groups);
    // sw.stop();
    // 输出

    // double elapsed_time = sw.ElapsedMillis();
    // cout << "(Range)Elapsed Time: " << elapsed_time << " ms" << endl;
    cout << "md5(" << input << ")=";
    for (size_t i = 0; i < res.size(); i++) {
        cout << hex << res[i];
    }
}

TEST(TestMD5, testSalt) {
    char input[] = "HelloWorld";


}


#endif
