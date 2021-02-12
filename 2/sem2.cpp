#include<tuple>
#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <list>
//#include <boost/circular_buffer.hpp>

struct X{

    int a : 4;
    char f : 1;
};


union Y {
    long a;
    int b;
    char c;
};

int main(){

    std::tuple<int, char, bool> t(2, 's', true);
    auto t2 = std::make_tuple(3, 'r', false);

    std::cout << std::get<1>(t2);

    std::array<int, 1> a = {0};

    std::deque<bool> d;

    std::list<int> l1, l2;
    for (auto i = 1; i < 6; ++i) {
        l1.push_back(i-1);
        l2.push_front(i);
    }
    l1.splice(std::next(std::begin(l1), 2),
              l2, std::next(std::begin(l2), 1),
              std::prev(std::end(l2),1)
              );

     for(auto j : l1)
         std::cout << j << " ";

    return 0;
}