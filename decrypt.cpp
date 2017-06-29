#include "decrypt.h"

Decrypt::Decrypt(string inp)
{
    input = inp;
}
//Implement full decryption algorithm
string Decrypt::createPlaintext()
{
    string plaintext;

    if (!key1 || !key2 || !key3 || !key4 || !key5)
    {
        return "NO KEY HAS BEEN ENTERED";
    }

    plaintext = input;

    if (plaintext == "")
    {
        return plaintext;
    }
    plaintext = this->decryptD(plaintext);
    plaintext = this->decryptC(plaintext);
    plaintext = this->decryptB(plaintext);
    plaintext = this->decryptA(plaintext);

    return plaintext;
}
//Replace characters in a string funcion
void Decrypt::replaceChars(string& subject, const string& search, const string& replace) //Not my code
{
     size_t pos = 0;
     while ((pos = subject.find(search, pos)) != string::npos)
     {
          subject.replace(pos, search.length(), replace);
          pos = pos + replace.length();
     }
}
//Decrypt DELTA
string Decrypt::decryptD(string inp)
{
    int num = key5;
    int size = inp.length();

    for(int i = 0; i < size; i++){
        long long int temp = (int)inp[i];
        temp = temp + (num * i);

        if (temp > 126)
        {
            while(temp > 126)
            {
                temp = 31 + (temp - 126);
            }
        }
        inp[i] = temp;
    }
    return inp;
}
//Decrypts CHARLIE
string Decrypt::decryptC(string inp)
{
    vector<string> encryptedA;
    vector<string> encryptedTest;

    for (unsigned i = 0; i < inp.length(); i += key4) {
        encryptedTest.push_back(inp.substr(i, key4));
    }
    int lastStringSize = encryptedTest[encryptedTest.size()-1].size();
    //Account for last string not being key4 size
    encryptedA.push_back(inp.substr(0, lastStringSize));
    inp.erase(0, lastStringSize);
    //Split the plaintext into multiple strings of key4 6
    for (unsigned j = 0; j < inp.length(); j += key4) {
        encryptedA.push_back(inp.substr(j, key4));
    }
    //Switch characters in every string in the vector
    for (unsigned i = 1, j = 2; i < encryptedA.size()-1; i += 2, j += 2){
        if ((i+1) >= encryptedA.size() || (j+1) >= encryptedA.size() )
        {
            break;
        }
        swap(encryptedA[i], encryptedA[j]);
    }
    //reverse the vector then append all strings into cyphertext
    reverse(encryptedA.begin(), encryptedA.end());
    string plaintext;
    for (unsigned i = 0; i < encryptedA.size(); i++){
        plaintext.append(encryptedA[i]);
    }
    return plaintext;
}
//Decrypt BRAVO
string Decrypt::decryptB(string inp)
{
    int num = key2;
    int size = inp.length();

    for(int i = 0; i < size; i++){
        long long int temp = (int)inp[i];
        temp = temp - (num * key1) - (i * i * (i + key2) * (i + key2));

        if (temp < 32)
        {
            while(temp < 32)
            {
                temp = 127 - (32 - temp);
            }
        }
        inp[i] = temp;
    }
    return inp;
}
//Decrypt ALPHA
string Decrypt::decryptA(string inp)
{
    vector<string> encryptedA;
    vector<string> encryptedTest;

    for (unsigned i = 0; i < inp.length(); i += key3) {
        encryptedTest.push_back(inp.substr(i, key3));
    }
    int lastStringSize = encryptedTest[encryptedTest.size()-1].size();
    //Account for last string not being size 10
    encryptedA.push_back(inp.substr(0, lastStringSize));
    inp.erase(0, lastStringSize);
    //Split the plaintext into multiple strings of size 10
    for (unsigned j = 0; j < inp.length(); j += key3) {
        encryptedA.push_back(inp.substr(j, key3));
    }
    //Switch characters in every string in the vector
    for (unsigned k = 0; k < encryptedA.size(); k++){
        for (unsigned i = 0, j = 1; i < encryptedA[k].length(); i += 2, j += 2){
            if (!encryptedA[k][i+1] || !encryptedA[k][j+1] )
            {
                break;
            }
            char temp = encryptedA[k][i];
            encryptedA[k][i] = encryptedA[k][j];
            encryptedA[k][j] = temp;
        }
    }

    //reverse the vector then append all strings into cyphertext
    reverse(encryptedA.begin(), encryptedA.end());
    string plaintext;
    for (unsigned i = 0; i < encryptedA.size(); i++){
        plaintext.append(encryptedA[i]);
    }
    return plaintext;
}
void Decrypt::setKey1(long k)
{
    key1 = k;
}
void Decrypt::setKey2(long k)
{
    key2 = k;
}
void Decrypt::setKey3(long k)
{
    key3 = k;
}
void Decrypt::setKey4(long k)
{
    key4 = k;
}
void Decrypt::setKey5(long k)
{
    key5 = k;
}
