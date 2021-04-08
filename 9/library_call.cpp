#include <iostream>
#include <filesystem>

#include <boost/dll.hpp>

int main(int argc, char ** argv)
{
	const std::filesystem::path path = "../Debug/dll.dll";

	const std::string name = "run";

	try
	{
		auto function =
			boost::dll::import_alias < int(int) > (path.string(), name);

		std::cout << function(42) << std::endl;
	}
	catch (const std::exception & exception)
	{
		std::cerr << exception.what() << std::endl;
	}

	system("pause");

	return EXIT_SUCCESS;
}