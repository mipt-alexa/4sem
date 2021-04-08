#define BOOST_DATE_TIME_NO_LIB

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>

int main(int argc, char ** argv)
{
	system("pause");

	const std::string shared_memory_name = "shared_memory";

	boost::interprocess::shared_memory_object shared_memory(
		boost::interprocess::open_only, shared_memory_name.c_str(), boost::interprocess::read_only);

	boost::interprocess::mapped_region region(shared_memory, boost::interprocess::read_only);

	auto memory = static_cast < char* >(region.get_address());

	for (std::size_t i = 0; i < region.get_size(); ++i)
	{
		if (*memory++ != 1)
		{
			std::cout << "shared memory corruption" << std::endl;
		}
	}
	
	std::cout << "shared memory correct" << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}