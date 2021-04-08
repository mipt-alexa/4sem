#define BOOST_DATE_TIME_NO_LIB

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

int main(int argc, char ** argv)
{
	system("pause");

	std::filesystem::path path = "../file.txt";
	const std::size_t length = 1024;

	boost::interprocess::file_mapping file_mapping(
		path.string().c_str(), boost::interprocess::read_only);

	boost::interprocess::mapped_region region(
		file_mapping, boost::interprocess::read_only);

	auto memory = static_cast < char* > (region.get_address());
		
	for (std::size_t i = 0; i < region.get_size(); ++i)
	{
		if (*memory++ != 'A')
		{
			std::cout << "file mapping corrupted" << std::endl;
		}
	}
		
	std::cout << "file mapping correct" << std::endl;

	std::fstream fin(path.string(), std::ios::in);

	char c;

	for (std::size_t i = 0; i < length; ++i)
	{
		fin >> c;

		if (c != 'A')
		{
			std::cout << "file corrupted" << std::endl;
		}
	}
	
	std::cout << "file correct" << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}