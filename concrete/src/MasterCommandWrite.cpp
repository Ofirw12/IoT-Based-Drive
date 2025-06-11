#include <iostream>

#include "MasterCommandWrite.hpp"

#include "ResponseManager.hpp"

#include "Handleton.hpp"
#include "MinionManager.hpp"
#include "NBDWriteArgs.hpp"

using namespace ilrd;

std::optional<std::pair<std::function<bool()>, std::chrono::milliseconds>>
	   MasterCommandWrite::Run(const std::shared_ptr<ITaskArgs> args)
{
	const auto taskArgs = std::static_pointer_cast<NBDWriteArgs>(args);
	Handleton::GetInstance<MinionManager>()->AddWriteTask(taskArgs->GetOffset(),
										taskArgs->GetLen(), taskArgs->GetUID(), taskArgs->GetStr());
	std::pair<std::function<bool()>, std::chrono::milliseconds> result;

#ifndef NDEBUG
	std::cout << "Running CommandWrite" << std::endl;
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