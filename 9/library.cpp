#include <iostream>

#include <boost/dll.hpp>

#define API extern "C" BOOST_SYMBOL_EXPORT

namespace library
{
	int f(int value)
	{
		std::cout << "Hello from DLL!" << std::endl;

		return value;
	}
}

BOOST_DLL_ALIAS(library::f, run);