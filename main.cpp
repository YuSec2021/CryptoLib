#include <iostream>

#include "Symmetric/AES/AES.h"

using namespace std;

int main() {
    AES aes;
    unsigned char res =  aes.hexReplace(0x61);
    cout << hex << res << endl;
    cout << hex << aes.ReHexReplace(res) << endl;

    char a[] = "abcdefghijklmnop";

    std::vector<unsigned char> v;
    for (int i = 0; i < sizeof(a); i++) {
        unsigned char tmp = std::stoi(Tools::charToHex(a[i]), 0, 16);
        v.push_back(tmp);
    }

    aes.RowShift(v);


    vector<vector<unsigned char>> remixMatrics = {
        {0xE, 0xB, 0xD, 0x9},
        {0x9, 0xE, 0xB, 0xD},
        {0xD, 0x9, 0xE, 0xB},
        {0xB, 0xD, 0x9, 0xE}
    };

    vector<vector<unsigned char>> test = {
        {0xC9, 0xE5, 0xFD, 0x2B},
        {0x7A, 0xF2, 0x78, 0x6E},
        {0x63, 0x9C, 0x26, 0x67},
        {0xB0, 0xA7, 0x82, 0xE5}
    };

    vector<vector<unsigned char>> test2;
    aes.multiplyMatrices(mixMatrics, test, test2);

    //unsigned char x = aes.gfadd(2, 0xc9) ^ aes.gfadd(3, 0x7a) ^ 0x63 ^ 0xb0;

    //unsigned char y = 0xc9 ^ aes.gfadd(2, 0x7a) ^ aes.gfadd(3, 0x63) ^ 0xb0;

    return 0;
}