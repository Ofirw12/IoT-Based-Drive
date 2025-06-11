
#include <iostream>

#include "AsyncInjection.hpp"

bool GetRekt()
{
	srand(time(nullptr));
	if (rand() % 2)
	{
		std::cout << "!GetRekt" << std::endl;
		return false;
	}
	std::cout << "GetRekt" << std::endl;
	return true;
}

void TestAsyncInjection()
{
	new ilrd::AsyncInjection(GetRekt, std::chrono::milliseconds(1000));
}

int main()
{
	TestAsyncInjection();
	return 0;
}