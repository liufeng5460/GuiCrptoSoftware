#ifndef MYRSA_H
#define MYRSA_H
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <iostream>
#include <string>

#include <cryptopp/rsa.h>
#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <cryptopp/md5.h>
#include<cryptopp/sha.h>

using namespace std;
using namespace CryptoPP;
class MyRSA
{
public:
    MyRSA();

     string getKey(const char*keyFile);//输入秘钥的文件名，返回秘钥的内容
     void GenerateRSAKey(unsigned int keyLength, const char *privFilename,
             const char *pubFilename);//输入公私钥的文件名和长度，自动生成公私钥

private:
      AutoSeededRandomPool _rng;
};

#endif // MYRSA_H
