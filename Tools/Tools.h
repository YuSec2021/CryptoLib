//
// Created by YuSec on 2024/12/6.
//

#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

class Tools
{
public:
    static string charToHex(unsigned char c);
    static vector<vector<unsigned char>> convertToVectorOfVectors(const vector<unsigned char>& original);
    static string toHexString(vector<unsigned char> &vec);
    static unsigned int hexStringToInt(string str, int format);

    static vector<unsigned char> left_shift(vector<unsigned char> vec, size_t shift);

    static vector<unsigned char> right_shift(vector<unsigned char> vec, size_t shift);

    static void print_hex(const vector<unsigned char> &vec);
};



#endif //TOOLS_H
