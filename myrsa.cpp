#include "myrsa.h"

MyRSA::MyRSA()
{

}


/*
    输入秘钥文件的名称，读取秘钥返回字符串类型
*/
string MyRSA::getKey(const char*keyFile)
{
        string key;
        FileSource file(keyFile, true, new StringSink(key));
        return key;
}

void MyRSA::GenerateRSAKey(unsigned int keyLength, const char *privFilename,
        const char *pubFilename)
{
    RSAES_OAEP_SHA_Decryptor priv(_rng, keyLength);
    HexEncoder privFile(new FileSink(privFilename));
    priv.DEREncode(privFile);
    privFile.MessageEnd();

    RSAES_OAEP_SHA_Encryptor pub(priv);
    HexEncoder pubFile(new FileSink(pubFilename));
    pub.DEREncode(pubFile);
    pubFile.MessageEnd();
}
