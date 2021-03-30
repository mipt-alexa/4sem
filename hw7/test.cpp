#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <vector>
#include <random>


void f(uint64_t size, uint64_t& res){

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

    res = inner;

 }


class Thread_Guard
{
public:

    explicit Thread_Guard(std::thread & thread) noexcept :
            m_thread(thread)
    {}

    Thread_Guard			(const Thread_Guard &) = delete;

    Thread_Guard & operator=(const Thread_Guard &) = delete;

    ~Thread_Guard() noexcept
    {
        try
        {
            if (m_thread.joinable())
            {
                m_thread.join();
            }
        }
        catch (...)
        {
            // std::abort();
        }
    }

private:

    std::thread & m_thread;
};



int main()
{
    int num_threads = 4;
    std::vector<uint64_t> results(num_threads);
    std::vector<std::thread> threads(num_threads - 1);
    std::vector< Thread_Guard > guards;

    Thread_Guard guard0(threads[0]);
    Thread_Guard guard1(threads[1]);
    Thread_Guard guard2(threads[2]);


    uint64_t block_size =  10000;
    uint64_t r = 0;


         threads[0] = std::thread(f, block_size, r);


    return 0;
}
