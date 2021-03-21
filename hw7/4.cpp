#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include "Timer.h"
#include <random>
#include <numeric>


int main(){

    Timer t;

    std::ofstream txt_file;
    txt_file.open("../hw7/4_data.txt");

    const int n = 100000000;
    std::vector< int > v(n);

    std::random_device rd;
    std::mt19937 g(rd());

    std::generate(v.begin(), v.end(), g);

    txt_file << "std::for_each" << std::endl << std::endl << "parallel: ";


    t.run();
    std::for_each(std::execution::par, v.begin(), v.end(), [](int& x) { x *= -1;});
    t.stop(txt_file);

    txt_file << "sequenced: ";

    t.run();
    std::for_each(std::execution::seq, v.begin(), v.end(),  [](int& x) { x *= -1;});
    t.stop(txt_file);

    txt_file << std::endl << "std::partial_sum\n";

    std::vector< int > result(n);

    t.run();
    std::partial_sum(v.begin(), v.end(), result.begin(), std::multiplies<>());
    t.stop(txt_file);

    txt_file << "\nstd::inclusive_scan\n";

    t.run();
    std::inclusive_scan(std::execution::par, v.begin(), v.end(), result.begin(), std::multiplies<>());
    t.stop(txt_file);


    std::vector< int > v_1(n);

    std::generate(v_1.begin(), v_1.end(), g);

    txt_file << "\nstd::transform_reduce\n";

    t.run();
    std::cout << std::transform_reduce(std::execution::par, v.begin(), v.end(), v_1.begin(),0) << std::endl;
    t.stop(txt_file);

    txt_file << "\nstd::inner_product\n";

    t.run();
    std::cout << std::inner_product( v.begin(), v.end(), v_1.begin(), 0);
    t.stop(txt_file);

}