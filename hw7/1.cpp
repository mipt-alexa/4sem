#include <iostream>
#include <random>
#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <algorithm>
#include <iomanip>


uint64_t calculate_block(uint64_t size){

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution< long double > urd(-1, 1);

    long double x, y;
    uint64_t  inner = 0;

    for (int i = 0; i < size; ++i) {
        x = urd(gen);
        y = urd(gen);

        if (x*x + y*y < 1){
            inner++;
        }
    }
    return inner;
}


void parallel_pi(const uint64_t size)
{
    const std::size_t num_threads = std::thread::hardware_concurrency();

    const uint64_t block_size = size / num_threads;

    std::vector< std::future< uint64_t > > futures(num_threads);
    uint64_t inner = 0;

    for(auto & future : futures){

        future = std::async(calculate_block, block_size);

    }

    for(auto & future : futures){
        inner += future.get();
    }

    std::cout << "parallel: " << std::setprecision(6) << (long double) 4*inner/size << "\n";
}



int main(){

    const uint64_t n = 500000000;

    parallel_pi(n);


    uint64_t inner = calculate_block(n);

    std::cout << "sequenced: " << std::setprecision(6) << (long double) 4*inner/n;


//    RESULTS:
//
//    parallel: 3.14161
//    sequenced: 3.14161


    return 0;
}
