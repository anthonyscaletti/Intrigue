#include "encrypt.h"
#include "decrypt.h"
#include <fstream>

#define SUCCESS 0

int main()
{
    srand(time(NULL));
    int choice;

    cout << "|WELCOME TO INTRIGUE|"    << endl;

    while (choice != 3)
    {
        cout << "------------------------" << endl << endl;
        cout << "Enter '1' for Encryption" << endl;
        cout << "Enter '2' for Decryption" << endl;
        cout << "Enter '3' to  Exit"       << endl;
        cout << "------------------------" << endl;
        cout << "Selection: ";
        while(!(cin >> choice) || (choice != 1 && choice != 2 && choice != 3))
        {
            cin.clear();
            cin.ignore(999,'\n');
            cout << endl << "INVALID CHOICE, TRY AGAIN" << endl;
            cout << "Selection: ";
        }

        switch (choice)
        {
        case 1:
        {
            //ENCRYPT FILE AND OUTPUT IT TO A CYPHER FILE AND KEYS INTO KEY FILE
            string path, encOut, keysOut;
            string outEncPath, outKeyPath;

            cout << "Enter plaintext file path: ";
            cin >> path;
            cout << endl;

            ifstream plainFile(path);

            if (!plainFile)
                cout << "NO PLAINTEXT FILE SELECTED**" << endl;

            vector<string> line1(20000000);
            int i = 0;

            cout << "Enter output directory: ";
            cin >> outEncPath;
            cout << endl;

            cout << "Enter output name for Encrypted file: ";
            cin >> encOut;
            cout << endl;

            cout << "Enter output name for Keys file: ";
            cin >> keysOut;
            cout << endl;

            cout << "File Encrypting... " << endl;

            if (outEncPath.at(outEncPath.size()-1) != '/')
                outEncPath.append("/");

            outKeyPath = outEncPath;

            ofstream cypherFile, keyFile;
            cypherFile.open (outEncPath.append(encOut));
            keyFile.open (outKeyPath.append(keysOut));
            while(getline(plainFile, line1[i]))
            {
                string key;

                long key1 = rand() % 32767 + 10;
                long key2 = rand() % 899 + 100;
                long key3 = rand() % 13 + 2;
                long key4 = rand() % 13 + 2;
                long key5 = rand() % 899 + 100;

                key.append(to_string(key1));
                key.append(to_string(key2));

                if (key3 < 10)
                    key.append(to_string(0));
                key.append(to_string(key3));

                if (key4 < 10)
                    key.append(to_string(0));
                key.append(to_string(key4));

                key.append(to_string(key5));

                keyFile << key << endl;

                Encrypt encrypt(line1[i]);
                encrypt.setKey1(key1);
                encrypt.setKey2(key2);
                encrypt.setKey3(key3);
                encrypt.setKey4(key4);
                encrypt.setKey5(key5);
                string cypher = encrypt.createCypher();

                cypherFile << cypher << endl;
                i++;
            }
            keyFile.close();
            cypherFile.close();
            cout << "\nFILE ENCRYPTED SUCCESSFULLY\n\n";
            break;
        }
        case 2:
        {
            //DECRYPT FILE AND OUTPUT IT TO A PLAINTEXT FILE
            string path;
            string keyPath;
            string outPath;
            string decOut;

            cout << "Enter encrypted file path: ";
            cin >> path;
            cout << endl;

            cout << "Enter keys file path: ";
            cin >> keyPath;
            cout << endl;

            cout << "Enter output directory: ";
            cin >> outPath;
            cout << endl;

            cout << "Enter output name for Decrypted file: ";
            cin >> decOut;
            cout << endl;

            cout << "File Decrypting... " << endl;

            if (outPath.at(outPath.size()-1) != '/')
                outPath.append("/");

            ifstream cypherFile(path);

            if (!cypherFile)
                cout << "NO ENCRYPTED FILE SELECTED**" << endl;

            ifstream keyFile(keyPath);

            if (!keyFile)
                cout << "NO KEYS FILE SELECTED**" << endl;

            vector<string> line1(20000000);
            vector<string> line2(20000000);
            int i = 0;

            ofstream decryptedFile;
            decryptedFile.open (outPath.append(decOut));
            while(getline(cypherFile, line1[i]))
            {
                string key1, key2, key3, key4, key5;

                keyFile >> line2[i];

                key5 = key5 + (line2.at(i).at(line2.at(i).size()-3));
                key5 = key5 + (line2.at(i).at(line2.at(i).size()-2));
                key5 = key5 + (line2.at(i).at(line2.at(i).size()-1));
                line2.at(i).erase(line2.at(i).size()-3, line2.at(i).size()-1);

                key4 = key4 + (line2.at(i).at(line2.at(i).size()-2));
                key4 = key4 + (line2.at(i).at(line2.at(i).size()-1));
                line2.at(i).erase(line2.at(i).size()-2, line2.at(i).size()-1);

                key3 = key3 + (line2.at(i).at(line2.at(i).size()-2));
                key3 = key3 + (line2.at(i).at(line2.at(i).size()-1));
                line2.at(i).erase(line2.at(i).size()-2, line2.at(i).size()-1);

                key2 = key2 + (line2.at(i).at(line2.at(i).size()-3));
                key2 = key2 + (line2.at(i).at(line2.at(i).size()-2));
                key2 = key2 + (line2.at(i).at(line2.at(i).size()-1));
                line2.at(i).erase(line2.at(i).size()-3, line2.at(i).size()-1);

                key1 = key1 + (line2.at(i));

                long dkey1 = stoi(key1);
                long dkey2 = stoi(key2);
                long dkey3 = stoi(key3);
                long dkey4 = stoi(key4);
                long dkey5 = stoi(key5);

                Decrypt decrypt(line1[i]);
                decrypt.setKey1(dkey1);
                decrypt.setKey2(dkey2);
                decrypt.setKey3(dkey3);
                decrypt.setKey4(dkey4);
                decrypt.setKey5(dkey5);
                string plaintext = decrypt.createPlaintext();

                decryptedFile << plaintext << endl;
                i++;
            }
            decryptedFile.close();
            cout << "\nFILE DECRYPTED SUCCESSFULLY\n\n";
            break;

        }

        case 3:
            break;
        }
    }

    cout << "\nINTRIGUE HAS TERMINATED SUCCESSFULLY\n\n";
    return SUCCESS;
}
