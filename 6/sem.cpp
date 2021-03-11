#include <iostream>

int main(){

    int x;

    std::cin >> x;

    std::cout << std::cin.fail();

    std::cin.clear();

    std::cin.ignore(100);

    std::cout << std::cin.fail();


    return 0;
}