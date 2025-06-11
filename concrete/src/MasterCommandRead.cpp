//
// Created by ofir on 4/6/25.
//
#include <iostream>

#include "MasterCommandRead.hpp"

#include <ResponseManager.hpp>

#include "Handleton.hpp"
#include "MinionManager.hpp"
#include "NBDReadArgs.hpp"

using namespace ilrd;

std::optional<std::pair<std::function<bool()>, std::chrono::milliseconds>>
	  MasterCommandRead::Run(std::shared_ptr<ITaskArgs> args)
{
	const auto taskArgs = std::static_pointer_cast<NBDReadArgs>(args);
	Handleton::GetInstance<MinionManager>()->AddReadTask(taskArgs->GetOffset(),
										taskArgs->GetLen(), taskArgs->GetUID());
	std::pair<std::function<bool()>, std::chrono::milliseconds> result;

#ifndef NDEBUG
	std::cout << "Running CommandRead" << std::endl;
#endif
	int counter = 0;
	result.first = [uid = taskArgs->GetUID(), &counter]
	{
		if (Handleton::GetInstance<ResponseManager>()->Contains(uid))
		{
			if (++counter == 10)
			{
				Handleton::GetInstance<ResponseManager>()->Remove(uid);
			}
			return false;
		}
		return true;
	};
	result.second = std::chrono::milliseconds(100);
	return result;
}