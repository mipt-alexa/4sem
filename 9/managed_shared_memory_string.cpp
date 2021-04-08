#define BOOST_DATE_TIME_NO_LIB

#include <iostream>
#include <string>

#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

int main(int argc, char ** argv)
{
	using allocator = boost::interprocess::allocator < char,
		boost::interprocess::managed_shared_memory::segment_manager > ;

	using string = boost::interprocess::basic_string < char, 
		std::char_traits < char >, allocator> ;

	const std::string shared_memory_name = "managed_shared_memory";

	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());

	boost::interprocess::managed_shared_memory shared_memory(
		boost::interprocess::open_or_create, shared_memory_name.c_str(), 1024);

	auto s = shared_memory.find_or_construct < string > ("String")("Hello",
		shared_memory.get_segment_manager());

	*s += ", world!";

	std::cout << *s << std::endl;

	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());

	system("pause");

	return EXIT_SUCCESS;
}