//
// Created by ofir on 4/20/25.
//
#include "MinionCommandRead.hpp"

#include <iostream>

#include "FileManager.hpp"
#include "Handleton.hpp"
#include "MasterProxy.hpp"
#include "MinionReadArgs.hpp"

std::optional<std::pair<std::function<bool()>, std::chrono::milliseconds>> ilrd
::MinionCommandRead::Run(std::shared_ptr<ITaskArgs> taskArgs)
{
	const auto args = std::static_pointer_cast<MinionReadArgs>(taskArgs);
	bool res = false;
	try
	{
#ifndef NDEBUG
		std::cout << "MinionCommandRead::Run:: Reading from offset " << args->GetOffset() << std::endl;
#endif
		res = Handleton::GetInstance<FileManager>()->Read(args->GetOffset(), args->GetLen(), args->GetData());
	}
	catch(...)
	{
		Handleton::GetInstance<MasterProxy>()->SendReadResponse(false, args->GetData(), args->GetLen(), args->GetUID());
	}

	Handleton::GetInstance<MasterProxy>()->SendReadResponse(res, args->GetData(), args->GetLen(), args->GetUID());
	return {};
}
