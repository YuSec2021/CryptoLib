//
// Created by YuSec on 2024/12/14.
//

#include "Tools.h"
#include "gtest/gtest.h"

using namespace std;

#ifdef TOOLS_TEST
TEST(TestTools, TestcharToHex) {

}

TEST(TestTools, TestconvertToVectorOfVectors) {

}

TEST(TestTools, TesttoHexString) {

}

TEST(TestTools, TesthexStringToInt) {
    string str = "1234";
    cout << "set 10, res:" << Tools::hexStringToInt(str, 10) << endl;
    cout << "set 16, res:" << Tools::hexStringToInt(str, 16) << endl;
}

TEST(TestTools, TestLeftShift) {
    /*vector<unsigned char> num = {0x12, 0x34, 0x56, 0x78};
    cout << "Original: ";
    Tools::print_hex(num);

    vector<unsigned char> left_shifted = Tools::left_shift(num, 4);
    cout << "Left shifted by 4 bits: ";
    Tools::print_hex(left_shifted);

    left_shifted = Tools::left_shift(num, 8);
    cout << "Left shifted by 8 bits: ";
    Tools::print_hex(left_shifted);*/

    vector<unsigned char> num2 = {0xff, 0xf1, 0xf0, 0xf2};
    cout << "Original: ";
    Tools::print_hex(num2);
    vector<unsigned char> left_shifted = Tools::left_shift(num2, 50);
    cout << "Left shifted by 50 bits: ";
    Tools::print_hex(left_shifted);

    num2 = {0x80, 0xf1, 0xf0, 0xf2};
    cout << "Original: ";
    Tools::print_hex(num2);
    left_shifted = Tools::left_shift(num2, 50);
    cout << "Left shifted by 50 bits: ";
    Tools::print_hex(left_shifted);


}

TEST(TestTools, TestRightShift) {

}

TEST(TestTools, TestRotate) {
    ASSERT_EQ(0x34567812, Tools::rotate_left(0x12345678, 8));
    ASSERT_EQ(0x78123456, Tools::rotate_right(0x12345678, 8));
}

#endif