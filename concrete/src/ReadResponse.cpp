
#include <iostream>

#include "ReadResponse.hpp"

void ilrd::ReadResponse::onSuccess(const std::shared_ptr<TaskResult>& res)
{
#ifndef NDEBUG
	std::cout << "ReadResponse::onSuccess()" << std::endl;
#endif
}

void ilrd::ReadResponse::onFailure(const std::shared_ptr<TaskResult>& res)
{
#ifndef NDEBUG
	std::cout << "ReadResponse::onFailure()" << std::endl;
#endif
}
