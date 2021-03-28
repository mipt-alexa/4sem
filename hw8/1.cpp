#include <iostream>
#include <random>
#include <vector>
#include <future>
#include <iomanip>
#include <condition_variable>
#include <atomic>


void calculate_block(uint64_t size,  std::atomic< uint64_t >& inner){

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution< long double > urd(-1, 1);

    long double x, y;

    for (int i = 0; i < size; ++i) {
        x = urd(gen);
        y = urd(gen);

        if (x*x + y*y < 1){
            inner++;
        }
    }

}


void parallel_pi(const uint64_t size)
{
    const std::size_t num_threads = std::thread::hardware_concurrency();

    const uint64_t block_size = size / num_threads;

    std::vector< std::future< void > > futures(num_threads);
    std::atomic< uint64_t > inner = 0;

    for(auto & future : futures){

        future = std::async(calculate_block, block_size, std::ref(inner));

        future.get();
    }

    std::cout << "parallel: " << std::setprecision(6) << (long double) 4*inner/size << "\n";
}



int main(){

    const uint64_t n = 50000000;

    parallel_pi(n);


    return 0;
}
