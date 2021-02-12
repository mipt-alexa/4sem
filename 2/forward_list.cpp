#include <forward_list>
#include <iostream>
#include <string>

void print(const std::string & message, 
	const std::forward_list < int > & forward_list_1,
	const std::forward_list < int > & forward_list_2)
{
	std::cout << message << std::endl;

	std::cout << "forward_list_1: ";

	for (const auto element : forward_list_1)
	{
		std::cout << element << ' ';
	}
	std::cout << std::endl;

	std::cout << "forward_list_2: ";

	for (const auto element : forward_list_2)
	{
		std::cout << element << ' ';
	}
	std::cout << std::endl << std::endl;
}

int main(int argc, char ** argv)
{
	std::forward_list < int > forward_list_1 = { 1, 2, 3, 4 };
	std::forward_list < int > forward_list_2 = { 77, 88, 99 };

	print("initial: ", forward_list_1, forward_list_2);

	forward_list_2.insert_after(forward_list_2.before_begin(), 99);
	forward_list_2.push_front(10);
	forward_list_2.insert_after(forward_list_2.before_begin(), { 10, 11, 12, 13 });

	print("insert: ", forward_list_1, forward_list_2);

	forward_list_2.erase_after(forward_list_2.begin());

	print("erase: ", forward_list_1, forward_list_2);

	forward_list_1.sort();
	forward_list_2 = forward_list_1;
	forward_list_2.unique();

	print("unique: ", forward_list_1, forward_list_2);

	forward_list_1.merge(forward_list_2);

	print("merge: ", forward_list_1, forward_list_2);

	system("pause");

	return EXIT_SUCCESS;
}