#include <iostream>
#include <SFML/Graphics.hpp>



class Parent{
public:
    int a;
    int b;

    Parent(int a1, int a2){
        a = a1;
        b = a2;
    };
};

class Child : public Parent{
public:

    Child(int a, int b) : Parent(a, b){

    }
};


int main(){

    auto* y = new Child(1, 4);

    std::cout << y->a << " " << y->b;

    int a = static_cast<int> (sf::VideoMode::getDesktopMode().width);

    std::cout << a;

    std::vector< int* > vec;

}