#include "myaes.h"
#include <time.h>
#include <unistd.h>
MyAES::MyAES()
{
}

MyAES::~MyAES()
{

}

void MyAES::setKey(string key,string iv){
    this->Key=key;
    this->Iv=iv;
}

void MyAES::getKey()
{
   cout<<"key is:"<<Key;
   cout<<"Iv is"<<Iv;
}

bool MyAES::GenerateKey(int length)
{
    if(length!=16 && length!=24 && length!=32){
        cerr<<"输入秘钥长度有误，只有16、24、 32三种";
        return false;
    }else{
            AutoSeededRandomPool rnd;
            byte key1[length];
            rnd.GenerateBlock(key1, length);
            // Generate a random IV
            byte iv1[length];
            rnd.GenerateBlock(iv1, length);

            HexEncoder encoder;
            encoder.Attach( new StringSink( Key ) );

            encoder.Put( key1, sizeof(key1 ) );
            encoder.MessageEnd();

            HexEncoder encoder1;
            encoder1.Attach( new StringSink( Iv ) );

            encoder1.Put( iv1, sizeof(iv1 ) );
            encoder1.MessageEnd();
            return true;
    }

}

/*
加密字符串，返回密文
 */
string MyAES::Encrypt(const string &plainText)
{
    string cipher,key, iv;
    StringSource ssk(Key, true /*pumpAll*/,
    new HexDecoder(
        new StringSink(key)
    ) // HexDecoder
); // StringSource

    StringSource ssv(Iv, true /*pumpAll*/,
        new HexDecoder(
            new StringSink(iv)
        ) // HexDecoder
    ); // StringSource
    CBC_Mode<AES>::Encryption aesEncryptor;

    aesEncryptor.SetKeyWithIV((byte const*) key.data(), key.size(), (byte const*) iv.data());

    StringSource(plainText, true,
            new StreamTransformationFilter(aesEncryptor,
                    new StringSink(cipher)));
    return cipher;
}

/*
解密字符串，返回解密后明文
 */
string MyAES::Decrypt(const string & cipher)
{
    string recover,key, iv;
    StringSource ssk(Key, true /*pumpAll*/,
    new HexDecoder(
        new StringSink(key)
    ) // HexDecoder
); // StringSource

    StringSource ssv(Iv, true /*pumpAll*/,
        new HexDecoder(
            new StringSink(iv)
        ) // HexDecoder
    ); // StringSource

    CBC_Mode<AES>::Decryption aesDecryptor;
    aesDecryptor.SetKeyWithIV((byte const*) key.data(), key.size(), (byte const*) iv.data());

    StringSource(cipher, true,
            new StreamTransformationFilter(aesDecryptor,
                    new StringSink(recover)));
    return recover;
}

//加密文件，输入需要加密文件的文件名和加密后文件的文件名
bool MyAES::EncryptFile(const string & inFilename, const string & outFilename)
{
    // check if the file 'inFilename' exists.
    if (access(inFilename.c_str(), 0) == -1)
    {
        cout << "The file " << inFilename << " is not exist! " << endl;
        return false;
    }
    // file exists, the encrypt the file
     string key, iv;
    StringSource ssk(Key, true /*pumpAll*/,
    new HexDecoder(
        new StringSink(key)
    ) // HexDecoder
); // StringSource

    StringSource ssv(Iv, true /*pumpAll*/,
        new HexDecoder(
            new StringSink(iv)
        ) // HexDecoder
    ); // StringSource
    CBC_Mode<AES>::Encryption aesEncryptor;

    aesEncryptor.SetKeyWithIV((byte const*) key.data(), key.size(), (byte const*) iv.data());

    FileSource(inFilename.c_str(), true,
            new StreamTransformationFilter(aesEncryptor,
                    new FileSink(outFilename.c_str())));

    return true;
}

//解密文件，输入需要解密的文件名和解密后的文件名
bool MyAES::DecryptFile(const string & decFilename,
        const string & recoverFilename)
{
    // check if the file 'decFilename' exists!
    if (access(decFilename.c_str(), 0) == -1)
    {
        cout << "The file " << decFilename << " is not exist! " << endl;
        return false;
    }
    // exist , then decrypt the file
     string key, iv;
    StringSource ssk(Key, true /*pumpAll*/,
    new HexDecoder(
        new StringSink(key)
    ) // HexDecoder
); // StringSource

    StringSource ssv(Iv, true /*pumpAll*/,
        new HexDecoder(
            new StringSink(iv)
        ) // HexDecoder
    ); // StringSource

    CBC_Mode<AES>::Decryption aesDecryptor;
    aesDecryptor.SetKeyWithIV((byte const*) key.data(), key.size(), (byte const*) iv.data());
    FileSource(decFilename.c_str(), true,
            new StreamTransformationFilter(aesDecryptor,
                    new FileSink(recoverFilename.c_str())));
    return true;
}
//从本地导入秘钥，输入秘钥所在位置及文件名
void MyAES::LoadKey(const char * KeyFilename){
    string str;
    FileSource file(KeyFilename, true, new StringSink(str));

    setKey(str.substr(0,str.size()/2),str.substr(str.size()/2,str.size()/2));
}
//保存秘钥，输入保存秘钥的名称（包含位置，绝对路径）
void MyAES::SaveKey(const char * KeyFilename){
    FileSink sink(KeyFilename);
    sink.Put((byte const*) Key.data(), Key.size());
    sink.Put((byte const*) Iv.data(), Iv.size());
}

