//
// Created by YuSec on 2024/12/6.
//

#ifndef SHA256_H
#define SHA256_H



class SHA256 {
public:
    void init();
    void padding();
    void update();
    void finalize();
};



#endif //SHA256_H
