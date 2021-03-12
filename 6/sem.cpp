#include <iostream>
#include <fstream>
#include <string>

int main(){

    int x;

    std::cin >> x;

    std::cout << std::cin.fail();
    std::cout << std::cin.eof();

//    std::cin.clear();
//
//    std::cin.ignore(1);
//
//    std::cout << std::cin.fail();


//    std::fstream fout("../6/file.txt", std::ios::out | std::ios::trunc);
//
//    for (int i = 0; i < 10; ++i) {
//        fout << "hello" + std::to_string(i) << "\n";
//    }

//    fout.close();
//
//    std::fstream fin("../6/file.txt", std::ios::in | std::ios::ate);
//
//    std::cout << fin.tellg();
//    fin.seekg(40, std::ios::beg);
//    fin.seekg(5, std::ios::cur);
//    std::cout << fin.tellg();
//
//    std::string line;
//
//    std::getline(fin, line);
//
//    std::cout << line;

    return 0;
}