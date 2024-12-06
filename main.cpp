#include <iostream>

#include "Symmetric/AES/AES.h"

using namespace std;

int main() {
    AES aes;
    cout << hex << aes.hexReplace("61") << endl;

    return 0;
}