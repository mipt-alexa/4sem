#include <iostream>
#include <set>

int main(int argc, char ** argv)
{
	std::set < int > set;

	set.insert(1);
	set.insert(2);
	set.insert(4);
	set.insert(5);
	set.insert(6);

	std::cout << "lower_bound(3): " << *set.lower_bound(3) << std::endl;
	std::cout << "upper_bound(3): " << *set.upper_bound(3) << std::endl;
	std::cout << "equal_range(3): " << 
		*set.equal_range(3).first << ' ' << *set.equal_range(3).second << std::endl;

	std::cout << std::endl;

	std::cout << "lower_bound(5): " << *set.lower_bound(5) << std::endl;
	std::cout << "upper_bound(5): " << *set.upper_bound(5) << std::endl;
	std::cout << "equal_range(5): " << 
		*set.equal_range(5).first << ' ' << *set.equal_range(5).second << std::endl;

	std::cout << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}