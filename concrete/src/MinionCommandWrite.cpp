

#include <iostream>

#include "MinionCommandWrite.hpp"
#include "FileManager.hpp"
#include "Handleton.hpp"
#include "MasterProxy.hpp"
#include "MinionWriteArgs.hpp"

std::optional<std::pair<std::function<bool()>, std::chrono::milliseconds>> ilrd
::MinionCommandWrite::Run(std::shared_ptr<ITaskArgs> taskArgs)
{
	const auto args = std::static_pointer_cast<MinionWriteArgs>(taskArgs);
	bool res = false;
	try
	{
#ifndef NDEBUG
		std::cout << "MinionCommandWrite::Run:: Writing to offset " << args->GetOffset() << std::endl;
		std::cout << "MinionCommandWrite::Run:: Wrote " << args->GetData() << std::endl;
#endif
		res = Handleton::GetInstance<FileManager>()->Write(args->GetOffset(),args->GetLen(), args->GetData());
	}
	catch(...)
	{
		Handleton::GetInstance<MasterProxy>()->SendWriteResponse(false, args->GetUID());
	}

	Handleton::GetInstance<MasterProxy>()->SendWriteResponse(res, args->GetUID());
	return {};
}
