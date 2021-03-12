#include <filesystem>
#include <iomanip>
#include <iostream>

int main(int argc, char ** argv)
{
	system("chcp 1251");

	auto path = std::filesystem::current_path() / "directory/file.txt";

	for (const auto & part : path)
	{
		std::cout << part.string() << std::endl;
	}

	std::cout << std::boolalpha <<
		"exists() = " << std::filesystem::exists(path) << std::endl <<
		"root_name() = " << path.root_name().string() << std::endl <<
		"root_directory() = " << path.root_directory().string() << std::endl <<
		"root_path() = " << path.root_path().string() << std::endl <<
		"relative_path() = " << path.relative_path().string() << std::endl <<
		"parent_path() = " << path.parent_path().string() << std::endl <<
		"filename() = " << path.filename().string() << std::endl <<
		"stem() = " << path.stem().string() << std::endl <<
		"extension() = " << path.extension().string() << std::endl;

	try
	{
		std::cout << "canonical() = " << std::filesystem::canonical(path).string() << std::endl;
	}
	catch (const std::filesystem::filesystem_error & exception)
	{
		std::cout << "exception: " << exception.what() << std::endl;

	}

	system("pause");

	return EXIT_SUCCESS;
}