#ifndef DECRYPT_H
#define DECRYPT_H

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <stdint.h>
#include <stdlib.h>

using namespace std;

class Decrypt
{
    private:
        string input;
        long key1 = -1;
        long key2 = -1;
        long key3 = -1;
        long key4 = -1;
        long key5 = -1;
    public:
        Decrypt(string inp);
        string createPlaintext();
        void replaceChars(string& subject, const string& search, const string& replace);
        string decryptD(string inp);
        string decryptC(string inp);
        string decryptB(string inp);
        string decryptA(string inp);
        void setKey1(long k);
        void setKey2(long k);
        void setKey3(long k);
        void setKey4(long k);
        void setKey5(long k);
};
#endif // DECRYPT_H
