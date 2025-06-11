//
// Created by ofir on 4/25/25.
//
#include <fstream>

int main()
{
	std::ofstream file{"a.dat"};
	for (size_t i = 0; i < 8*1024*1024; ++i)
	{
		file << '\0';
	}
	return 0;
}
