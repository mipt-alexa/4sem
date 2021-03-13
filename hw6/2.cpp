#include <fstream>
#include <string>
#include <random>
#include <iostream>
#include <cmath>


int main(){

    std::fstream file("../hw6/2_data.txt");

    std::random_device rd;
    std::mt19937 gen(rd());

    const int str_length = 7;
    const int file_length = 20;

    auto min = (unsigned int) pow(10, str_length - 1);
     auto max = (unsigned int) (pow(10,str_length) - 1);

    std::uniform_int_distribution<unsigned int> dis(min, max);

    for (int i = 0; i < file_length; ++i) {
        file << dis(gen) << std::endl;
    }

    int n;
    std::cin >> n;

    std::string buffer;

    if (n < 1 || n > file_length){
        std::cout << "string number out of range(";
    }else{
        file.seekg((n-1) * (str_length + 2) );
        std::getline(file, buffer);
        std::cout << buffer;
    }

    return 0;
}