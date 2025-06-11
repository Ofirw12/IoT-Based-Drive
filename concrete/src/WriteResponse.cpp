

#include <iostream>

#include "WriteResponse.hpp"

#include "Handleton.hpp"
#include "Logger.hpp"

void ilrd::WriteResponse::onSuccess(const std::shared_ptr<TaskResult>& res)
{
#ifndef NDEBUG
	std::cout << "WriteResponse::onSuccess()" << std::endl;
#endif
}

void ilrd::WriteResponse::onFailure(const std::shared_ptr<TaskResult>& res)
{
#ifndef NDEBUG
	std::cout << "WriteResponse::onFailure()" << std::endl;
#endif
}
