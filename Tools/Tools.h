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
    static string charToHex(char c);
    static vector<vector<unsigned char>> convertToVectorOfVectors(const vector<unsigned char>& original);
    static string toHexString(vector<unsigned char> &vec);
};



#endif //TOOLS_H
