#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include <random>
#include "Timer.h"


template < typename Iterator, typename T >
struct accumulate_block
{
    void operator()(Iterator first, Iterator last, T & result)
    {
        result = std::accumulate(first, last, result);
    }
};


template < typename Iterator, typename T >
T parallel_accumulate(Iterator first, Iterator last, T init, const std::size_t num_threads)
{
    const std::size_t length = std::distance(first, last);

    if (!length)
        return init;

    const std::size_t block_size = length / num_threads;

    std::vector < T > results(num_threads);
    std::vector < std::thread > threads(num_threads - 1);

    Iterator block_start = first;

    for (std::size_t i = 0; i < (num_threads - 1); ++i)
    {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);

        threads[i] = std::thread(
                accumulate_block < Iterator, T > (),
                block_start, block_end, std::ref(results[i])); // !

        block_start = block_end;
    }

    accumulate_block < Iterator, T > ()(block_start, last, results[num_threads - 1]);

    std::for_each(threads.begin(), threads.end(),
                  std::mem_fn(&std::thread::join));

    return std::accumulate(results.begin(), results.end(), init);
}


int main()
{
    Timer t;
    std::ofstream txt_file;
    txt_file.open("../hw7/2_data.txt");

    std::vector < int > v(100000000);

    std::random_device rd;
    std::mt19937 g(rd());

    std::generate(v.begin(), v.end(), g);


    std::vector<unsigned int> sizes(20);
    std::iota(sizes.begin(), sizes.end(), 1);


    for (unsigned int size : sizes) {

        txt_file << size << " ";

        t.run();

        std::cout << parallel_accumulate(v.begin(), v.end(), 0, size);

        t.stop(txt_file);

        txt_file << std::endl;

    }


    return 0;
}