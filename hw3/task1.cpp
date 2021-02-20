#include <set>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Timer.h"


int main(){

    Timer t;

    std::ofstream txt_file;
    txt_file.open("../hw3/mydata.txt");

    std::vector<unsigned int> sizes(25);
    sizes[0] = 10000;

    int i;
    for (i = 1; i < 10; ++i) {
        sizes[i] = 1.6*sizes[i-1];
    }
    for (; i < sizes.size(); ++i) {
        sizes[i] = 1.1*sizes[i-1];
    }

    std::set<int> set;
    std::vector<int> vec;

    for (auto j : sizes) {
        vec.reserve(j);
        txt_file << j << " ";

        for (int i = 0; i < j; ++i) {
            vec.push_back(j - i);
        }

        t.run();
        for (int i = 0; i < j; ++i) {
            set.insert(j - i);
        }
        t.stop(txt_file);

        t.run();
        std::sort(vec.begin(), vec.end());
        t.stop(txt_file);

        txt_file << std::endl;

        vec.clear();
        set.clear();
    }


}