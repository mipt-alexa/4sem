#include <iostream>
#include <unordered_set>
#include <string>
#include <utility>
#include <random>
#include <array>
#include <vector>
#include <fstream>


struct my_struct{
    my_struct(const uint16_t a1, const double b1, std::string  c1) :
            a(a1), b(b1), c(std::move(c1))
    {}

    uint16_t a;
    float b;
    std::string c;
};


template < typename T >
void hash_combine(std::size_t & seed, const T & value) noexcept
{
    seed ^= std::hash < T > ()(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template < typename T >
void hash_value(std::size_t & seed, const T & value) noexcept
{
    hash_combine(seed, value);
}

template < typename T, typename ... Types >
void hash_value(std::size_t & seed, const T & value, const Types & ... args) noexcept
{
    hash_combine(seed, value);
    hash_value(seed, args...);
}

template < typename ... Types >
std::size_t hash_value(const Types & ... args) noexcept
{
    std::size_t seed = 0;
    hash_value(seed, args...);
    return seed;
}

struct my_hash_func{
    std::size_t operator() (const my_struct & element) const noexcept
    {
        return hash_value(element.a, element.b, element.c);
    }
    };

struct my_equal{
    bool operator() (const my_struct & lhs, const my_struct & rhs) const noexcept
    {
        return (lhs.a == rhs.a);
    }
};

int main(){

    std::ofstream txt_file;
    txt_file.open("../hw3/mydata3.txt");

    std::unordered_set< my_struct, my_hash_func, my_equal> hash_table;

    int n = 40;
    std::vector<unsigned int> sizes;   //stores numbers of elements
    int n_min = 100000, n_max = 3000000;    // min and max sizes
    int step = (n_max - n_min) / n;

    for (int j = 0; j < n; ++j) {
        sizes.push_back(n_min + j*step);
    }

    std::array<char, 26> letters{};   //array for letters of latin alphabet
    letters[0] = 'a';
    for (int i = 1; i < 26; ++i) {
        letters[i] = letters[i-1] + 1;
    }

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

    std::uniform_real_distribution<> dis_float(FLT_MIN, FLT_MAX);
    std::uniform_int_distribution<> dis_uint(0, UINT16_MAX);
    std::uniform_int_distribution<> dis_str_len(0, 10);
    std::uniform_int_distribution<> dis_char(0, 25);

    std::string buffer_str;
    int str_len;

    for (auto size : sizes) {

        // filling the hash table:

        for (int j = 0; j < size; ++j) {

            str_len = dis_str_len(gen);
            for (int i = 0; i < str_len; ++i) {
                buffer_str += letters[dis_char(gen)];
            }

            hash_table.insert(my_struct(dis_uint(gen), dis_float(gen), buffer_str));

            buffer_str.clear();
        }

        txt_file << size <<  " " << size - hash_table.size() << std::endl;

        hash_table.clear();
    }

   /* for (const auto & it : hash_table)
    {
        std::cout << it.a << " "<< it.b <<" "<< it.c << std::endl;
    }*/

    return 0;
}