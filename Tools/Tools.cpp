//
// Created by YuSec on 2024/12/6.
//

#include "Tools.h"

std::string Tools::charToHex(char c) {
    std::ostringstream oss;
    oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(c));
    return oss.str();
}