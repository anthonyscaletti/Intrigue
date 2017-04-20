#include "encrypt.h"

Encrypt::Encrypt(string inp)
{
    input = inp;
}
//Implement full encryption algorithm
string Encrypt::createCypher()
{
    string cypher;

    cypher = input;

    if (cypher == "")
    {
        return cypher;
    }

    if (!key1 || !key2 || !key3 || !key4 || !key5)
    {
        return "MISSING KEY";
    }

    cypher = this->encryptA(cypher);
    cypher = this->encryptB(cypher);
    cypher = this->encryptC(cypher);
    cypher = this->encryptD(cypher);

    return cypher;
}
//Replace characters in a string funcion
void Encrypt::replaceChars(string& subject, const string& search, const string& replace) //Not my code
{
     size_t pos = 0;
     while ((pos = subject.find(search, pos)) != string::npos)
     {
          subject.replace(pos, search.length(), replace);
          pos = pos + replace.length();
     }
}
//Encrypt ALPHA
string Encrypt::encryptA(string inp)
{
    vector<string> encryptedA;

    //Split the plaintext into multiple strings of size 10
    for (unsigned i = 0; i < inp.length(); i += key3) {
        encryptedA.push_back(inp.substr(i, key3));
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
    string cyphertext;
    for (unsigned i = 0; i < encryptedA.size(); i++){
        cyphertext.append(encryptedA[i]);
    }


    return cyphertext;

}
//Encrypt BRAVO
string Encrypt::encryptB(string inp)
{
    int num = key2;
    int size = inp.length();

    for(int i = 0; i < size; i++){
        long long int temp = (int)inp[i];
        temp = temp + (num * key1) + (i * i * (i + key2) * (i + key2));

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
//Encrypt CHARLIE
string Encrypt::encryptC(string inp)
{
    vector<string> encryptedA;

    //Split the plaintext into multiple strings of key4 size
    for (unsigned i = 0; i < inp.length(); i += key4) {
        encryptedA.push_back(inp.substr(i, key4));
    }
    //reverse the vector
    reverse(encryptedA.begin(), encryptedA.end());

    //Switch characters in every string in the vector
    for (unsigned i = 1, j = 2; i < encryptedA.size()-1; i += 2, j += 2){
        if ((i+1) >= encryptedA.size() || (j+1) >= encryptedA.size() )
        {
            break;
        }
        swap(encryptedA[i], encryptedA[j]);

    }

    //Append all strings into cyphertext
    string cyphertext;
    for (unsigned i = 0; i < encryptedA.size(); i++){
        cyphertext.append(encryptedA[i]);
    }


    return cyphertext;

}
//Encrypt DELTA
string Encrypt::encryptD(string inp)
{

    int num = key5;
    int size = inp.length();

    for(int i = 0; i < size; i++){
        long long int temp = (int)inp[i];
        temp = temp - (num * i);

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
//Set symmetric key
void Encrypt::setKey1(long k)
{
    key1 = k;
}
void Encrypt::setKey2(long k)
{
    key2 = k;
}
void Encrypt::setKey3(long k)
{
    key3 = k;
}
void Encrypt::setKey4(long k)
{
    key4 = k;
}
void Encrypt::setKey5(long k)
{
    key5 = k;
}



