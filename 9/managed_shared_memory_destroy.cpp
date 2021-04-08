#define BOOST_DATE_TIME_NO_LIB

#include <iostream>
#include <string>

#include <boost/interprocess/managed_shared_memory.hpp>

int main(int argc, char ** argv)
{
	const std::string shared_memory_name = "managed_shared_memory";

	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());

	boost::interprocess::managed_shared_memory shared_memory(
		boost::interprocess::open_or_create, shared_memory_name.c_str(), 1024);

	auto i = shared_memory.find_or_construct < int > ("Integer")(42);

	std::cout << *i << std::endl;

	shared_memory.destroy < int > ("Integer");

	std::pair < int*, std::size_t > p = shared_memory.find < int > ("Integer");

	if (p.first)
	{
		std::cout << *p.first << std::endl;
	}

	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());

	system("pause");

	return EXIT_SUCCESS;
}