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

	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str()); // !

	boost::interprocess::shared_memory_object shared_memory(
		boost::interprocess::create_only, shared_memory_name.c_str(), boost::interprocess::read_write); 

	shared_memory.truncate(1024);

	boost::interprocess::mapped_region region(shared_memory, boost::interprocess::read_write);

	std::memset(region.get_address(), 1, region.get_size()); // !

	std::cout << "shared memory ready" << std::endl;

	system("pause");

	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str()); // !

	system("pause");

	return EXIT_SUCCESS;
}