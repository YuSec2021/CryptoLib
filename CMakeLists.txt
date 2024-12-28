cmake_minimum_required(VERSION 3.29.6)
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
        Asymmetric/RSA/RSA.h
        Symmetric/AES/test_AES.cpp
        Hash/MD5/test_MD5.cpp
        Hash/SHA1/test_SHA1.cpp
        Hash/SHA256/test_SHA256.cpp
        Symmetric/TEA/test_TEA.cpp
        Symmetric/XTEA/test_XTEA.cpp
        Symmetric/XXTEA/test_XXTEA.cpp
        Tools/test_Tools.cpp
        Asymmetric/RSA/test_RSA.cpp
        Hash/constants.h
)

add_subdirectory(./googletest-1.15.2)
include_directories(${PROJECT_SOURCE_DIR}/src/include ./googletest1.15.2/googletest/include)
link_directories(${PROJECT_SOURCE_DIR}/lib ${PROJECT_SOURCE_DIR}/googletest-1.15.2)
target_link_libraries(${PROJECT_NAME} gtest)