cmake_minimum_required(VERSION 3.30)
project(CryptoLib)

set(CMAKE_CXX_STANDARD 20)

add_executable(CryptoLib main.cpp
        Tools/Tools.cpp
        Tools/Tools.h
        Symmetric/AES/AES.cpp
        Symmetric/AES/AES.h
        Hash/MD5/MD5.cpp
        Hash/MD5/MD5.h
        Hash/SHA1/SHA1.cpp
        Hash/SHA1/SHA1.h
        Hash/SHA256/SHA256.cpp
        Hash/SHA256/SHA256.h
        Symmetric/constant.h
        Symmetric/TEA/TEA.cpp
        Symmetric/TEA/TEA.h
        Symmetric/XTEA/XTEA.cpp
        Symmetric/XTEA/XTEA.h
        Symmetric/XXTEA/XXTEA.cpp
        Symmetric/XXTEA/XXTEA.h
        Asymmetric/RSA/RSA.cpp
        Asymmetric/RSA/RSA.h)

add_subdirectory(./googletest-1.15.2)
include_directories(${PROJECT_SOURCE_DIR}/src/include ./googletest1.15.2/include)
link_directories(${PROJECT_SOURCE_DIR}/lib ${PROJECT_SOURCE_DIR}/googletest-1.15.2)
target_link_libraries(${PROJECT_NAME} gtest)