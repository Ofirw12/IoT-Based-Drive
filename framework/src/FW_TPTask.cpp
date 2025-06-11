
#include "FW_TPTask.hpp"

#include <iostream>

#include "AsyncInjection.hpp"
#include "Factory.hpp"
#include "Handleton.hpp"
#include "ICommand.hpp"
#include "Logger.hpp"


ilrd::FW_TPTask::FW_TPTask(const std::shared_ptr<ITaskArgs>& args)
	: m_taskArgs(args) {}


void ilrd::FW_TPTask::Run()
{
	std::shared_ptr<ICommand> command = nullptr;
	try
	{
		command = Handleton::GetInstance<Factory<int,
									ICommand>>()->Create(m_taskArgs->GetKey());
	}
	catch (...)
	{
		Handleton::GetInstance<Logger>()->
		Log("Got invalid key in FW_TPTask::Run()", Logger::ERROR);
		throw;
	}

	const std::optional<std::pair<std::function<bool()>, std::chrono::milliseconds>> ai_pair
													= command->Run(m_taskArgs);
	if (ai_pair)
	{
		new AsyncInjection(ai_pair->first, ai_pair->second);
	}
}
