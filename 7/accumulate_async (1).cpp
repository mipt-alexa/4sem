#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

template < typename Iterator, typename T >
T parallel_accumulate(Iterator first, Iterator last, T init)
{
	const std::size_t length = std::distance(first, last);

	const std::size_t max_size = 25;

	if (length <= max_size)
	{
		return std::accumulate(first, last, init);
	}
	else
	{
		Iterator middle = first;
		std::advance(middle, length / 2);

		std::future < T > first_half_result =
			std::async(parallel_accumulate < Iterator, T >, first, middle, init);

		T second_half_result = parallel_accumulate(middle, last, T());

		return first_half_result.get() + second_half_result;
	}
}

int main(int argc, char ** argv)
{
	std::vector < int > v(100);

	std::iota(v.begin(), v.end(), 1);

	std::cout << parallel_accumulate(v.begin(), v.end(), 0) << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}