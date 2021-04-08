#define BOOST_DATE_TIME_NO_LIB

#include <iostream>
#include <mutex>
#include <string>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>

int main(int argc, char ** argv)
{
	const std::string shared_memory_name = "managed_shared_memory";

	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());

	boost::interprocess::managed_shared_memory shared_memory(
		boost::interprocess::open_or_create, shared_memory_name.c_str(), 1024);

	auto i = shared_memory.find_or_construct < int > ("Integer")(42);

	const std::string mutex_name = "mutex";

	auto mutex = 
		shared_memory.find_or_construct < boost::interprocess::interprocess_mutex > (
			mutex_name.c_str())();

	{
		std::lock_guard < boost::interprocess::interprocess_mutex > lock(*mutex);

		std::cout << *i << std::endl;
	}

	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());

	system("pause");

	return EXIT_SUCCESS;
}