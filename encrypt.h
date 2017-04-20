#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <stdint.h>
#include <stdlib.h>

using namespace std;

class Encrypt
{
    private:
        string input;
        long key1 = -1;
        long key2 = -1;
        long key3 = -1;
        long key4 = -1;
        long key5 = -1;
    public:
        Encrypt(string inp);
        string createCypher();
        void replaceChars(string& subject, const string& search, const string& replace);
        string encryptA(string inp);
        string encryptB(string inp);
        string encryptC(string inp);
        string encryptD(string inp);
        void setKey1(long k);
        void setKey2(long k);
        void setKey3(long k);
        void setKey4(long k);
        void setKey5(long k);
};

#endif // ENCRYPT_H
