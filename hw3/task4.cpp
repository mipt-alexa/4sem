#include <iostream>
#include <unordered_set>
#include <string>
#include <utility>
#include <random>
#include <array>
#include <vector>
#include <fstream>
#include <functional>

unsigned int hash0(const char* str, unsigned int length)
{
    unsigned int b    = 378551;
    unsigned int a    = 63689;
    unsigned int hash = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = hash * a + (*str);
        a    = a * b;
    }

    return hash;
}

unsigned int hash1(const char* str, unsigned int length)
{
    unsigned int hash = 1315423911;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash ^= ((hash << 5) + (*str) + (hash >> 2));
    }

    return hash;
}

unsigned int hash2(const char* str, unsigned int length)
{
    const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    const unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
    const unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
    const unsigned int HighBits          =
            (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
    unsigned int hash = 0;
    unsigned int test = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash << OneEighth) + (*str);

        if ((test = hash & HighBits) != 0)
        {
            hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    return hash;
}

unsigned int hash3(const char* str, unsigned int length)
{
    unsigned int hash = 0;
    unsigned int x    = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash << 4) + (*str);

        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
        }

        hash &= ~x;
    }

    return hash;
}

unsigned int hash4(const char* str, unsigned int length)
{
    unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
    unsigned int hash = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash * seed) + (*str);
    }

    return hash;
}

unsigned int hash5(const char* str, unsigned int length)
{
    unsigned int hash = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (*str) + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

unsigned int hash6(const char* str, unsigned int length)
{
    unsigned int hash = 5381;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = ((hash << 5) + hash) + (*str);
    }

    return hash;
}

unsigned int hash7(const char* str, unsigned int length)
{
    unsigned int hash = length;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
    }

    return hash;
}

unsigned int hash8(const char* str, unsigned int length)
{
    unsigned int hash = 0xAAAAAAAA;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ (*str) * (hash >> 3)) :
                (~((hash << 11) + ((*str) ^ (hash >> 5))));
    }

    return hash;
}




int main(){

    std::ofstream txt_file;
    txt_file.open("../hw3/mydata4.txt");

    int n = 15;
    std::vector<unsigned int> sizes;   //stores numbers of elements
    int n_min = 100000, n_max = 1600000;    // min and max sizes
    int step = (n_max - n_min) / n;
    for (int j = 0; j < n; ++j) {
        sizes.push_back(n_min + j*step);
    }


    std::array<char, 26> letters{};   //array for letters of latin alphabet
    letters[0] = 'a';
    for (int i = 1; i < 26; ++i) {
        letters[i] = letters[i-1] + 1;
    }

    std::array<std::function<unsigned int(const char* str, unsigned int length)>, 9> hash_p;

    hash_p[0] = hash0;
    hash_p[1] = hash1;
    hash_p[2] = hash2;
    hash_p[3] = hash3;
    hash_p[4] = hash4;
    hash_p[5] = hash5;
    hash_p[6] = hash6;
    hash_p[7] = hash7;
    hash_p[8] = hash8;

    std::vector<std::unordered_set<unsigned int>> hash_val(9);  // stores sets of hash values for different functions


    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

    std::uniform_int_distribution<> dis_char(0, 25);

    std::string buffer_str;
    int str_len = 10;

    for (auto size : sizes) {

        // filling the hash tables:

        for (int j = 0; j < size; ++j) {

            for (int i = 0; i < str_len; ++i) {
                buffer_str += letters[dis_char(gen)];
            }

            for (int k = 0; k < 9; ++k) {
                hash_val[k].insert(hash_p[k](buffer_str.c_str(), buffer_str.length()));
            }

            buffer_str.clear();
        }


        txt_file << size ;
        for (int i = 0; i < 9; ++i) {
            txt_file << " " << size - hash_val[i].size();
            hash_val[i].clear();
        }
        txt_file << std::endl;
    }



    return 0;
}