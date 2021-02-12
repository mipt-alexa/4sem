#include <bitset>
#include <climits>
#include <iostream>
#include <numeric>

int main(int argc, char ** argv)
{
	enum Color 
	{
		red, yellow, green, blue, white, black, //...,
		quantity
	};

	std::bitset < quantity > colors;

	colors.set(red);
	colors.set(blue);

	std::cout << "bitfield of   used colors: " << colors			<< std::endl;
	std::cout << "quantity of   used colors: " << colors.count()	<< std::endl;
	std::cout << "bitfield of unused colors: " << ~colors			<< std::endl;

	std::cout << std::endl;

	if (colors.any()) 
	{
		for (int c = 0; c < quantity; ++c) 
		{
			if (colors[c]) 
			{
				std::cout << "color presented\n";
			}
		}
	}

	std::cout << std::endl;

	std::cout << "42 as binary long:     " << std::bitset < 32 > (42) << std::endl;

	std::string s = std::bitset < 32 > (12345678).to_string();
	std::cout << "12345678 with 32 bits: " << s << std::endl;

	std::cout << "1000101011 as number:  " << std::bitset < 32 > ("1000101011").to_ullong() << std::endl;

	std::cout << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}