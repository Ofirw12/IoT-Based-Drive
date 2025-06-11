
#include <iostream>

#include "AsyncInjection.hpp"

bool BoolFunc()
{
	srand(time(nullptr));
	if (random() % 2)
	{
		std::cout << "!GetRekt" << std::endl;
		return false;
	}
	std::cout << "GetRekt" << std::endl;
	return true;
}

void TestAsyncInjection()
{
	new ilrd::AsyncInjection(BoolFunc, std::chrono::milliseconds(1000));
}

int main()
{
	TestAsyncInjection();
	return 0;
}