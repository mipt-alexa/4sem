#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <vector>


template < typename Iterator, typename F>
void par_for_each(Iterator first, Iterator last, F l)
{
    const std::size_t length = std::distance(first, last);

    const std::size_t max_size = 25;

    if (length <= max_size)
    {
        std::for_each(first, last, l);
    }
    else
    {
        Iterator middle = first;
        std::advance(middle, length / 2);

        std::future < void > first_half_result =
                std::async(par_for_each < Iterator, F >, first, middle, l);

        par_for_each(middle, last, l);

    }
}

int main()
{
    std::vector < int > v(200);

    std::iota(v.begin(), v.end(), 0);

    par_for_each(v.begin(), v.end(), [](int& x) { x *= (x + 1); });

    for(auto x : v){
        std::cout << x << " ";
    }


    return 0;
}
