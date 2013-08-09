#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <limits.h>

using namespace std;

void makeRandomString(const int len, const unsigned int key, string& str)
{
    unsigned int seed = (0 == key) ? time(NULL) : key;

    srandom(seed);
    str.resize(len);
    string pad(16, '_');
    for (int i = 0; i < len; i += 512)
    {
        str.replace(i, 16, pad);

        int count = std::min(len - i, 512);
        unsigned int checksum = 0;
        for (int j = 16; j < count; j++)
        {
            str[i+j] = '@' + abs(random() % 63);
            checksum = (checksum * 31) + str[i+j];
        }
        cout << "mk checksum:" << checksum << endl;

        char buffer[32];
        int ret = sprintf(buffer, "%u", checksum);
        str.replace(i, ret, buffer);
    }
}

bool verifyRandomString(const string& str)
{
    int length = str.size();
    for (int i = 0; i < length; i += 512)
    {
        unsigned int chk = atoi(str.c_str() + i);

        int count = std::min(length - i, 512);
        unsigned int checksum = 0;
        for (int j = 16; j < count; j++)
        {
            checksum = (checksum * 31) + str[i+j];
        }

        if (checksum != chk)
        {
            cout << "cmp checksum:" << checksum << " vs " << chk << endl;
            return false;
        }
    }

    return true;
}

int main(int argc, const char *argv[])
{
    string str;
    unsigned int key = 0;

    for (int i = 0; i < 10; i++)
    {
        int len = (random() % 10 + 1) * 512;
        cout << "test len: " << len << "; ";
        unsigned int key0 = random();
        makeRandomString(len, key0, str);
        key = atoi(str.c_str());
        //cout << str << endl;
        cout << "key0: " << key0 << "; ";
        cout << "key: " << key << "; ";
        cout << "verified: " << verifyRandomString(str) << endl;
    }
    return 0;
}

