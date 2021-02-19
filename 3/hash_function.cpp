#include <iostream>

std::size_t hash(const char * s)
{
	auto h = 0U;

	for (auto p = s; *p != '\0'; ++p)
	{
		h = h * 31 + static_cast < unsigned int > (*p);
	}

	return h % 128;
}

int main(int argc, char ** argv)
{
	std::cout << hash("ivanov") << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}

// i 105
// v 118
// a 97
// n 110
// o 111
// v 118

// h = 0 * HASH_MUL + 105
// h = 105 * HASH_MUL + 118
// h = 3373 * HASH_MUL + 97
// h = 104660 * HASH_MUL + 110
// h = 3244570 * HASH_MUL + 111
// h = 100581781 * HASH_MUL + 118
// return 3118035329 % HASH_SIZE

// hash("ivanov") = 1