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

	boost::interprocess::file_mapping::remove(path.string().c_str());

	std::fstream fout(path.string(), std::ios::out | std::ios::trunc);

	std::fill_n(std::ostream_iterator < char > (fout), length, 0);

	fout.close();

	boost::interprocess::file_mapping file_mapping(
		path.string().c_str(), boost::interprocess::read_write);

	boost::interprocess::mapped_region region(
		file_mapping, boost::interprocess::read_write);

	std::memset(region.get_address(), 'A', region.get_size());

	std::cout << "file mapping ready" << std::endl;

	system("pause");

	boost::interprocess::file_mapping::remove(path.string().c_str());

	system("pause");

	return EXIT_SUCCESS;
}