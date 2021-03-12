#include <fstream>
#include <string>
#include <random>
#include <sstream>
#include <iostream>

int main(){

    std::fstream file("../hw6/2_data.txt");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned int> dis(1000000,9999999);

    for (int i = 0; i < 20; ++i) {
        file << dis(gen) << std::endl;
    }

    int n;
    std::cin >> n;

    std::string buffer;

    if (n < 1 || n > 20){
        std::cout << "string number out of range(";
    }else{
        file.seekg((n-1)*9);
        std::getline(file, buffer);
        std::cout << buffer;
    }

    return 0;
}