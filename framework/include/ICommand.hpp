/*******************************************************************************
* FileName: ICommand                                                           *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: Gil Fridman					                                   *
 * Review Status: APPROVED (30/03/2025)                                        *
 ******************************************************************************/

#ifndef ILRD_RD1645_ICOMMAND_HPP
#define ILRD_RD1645_ICOMMAND_HPP

#include <memory>
#include <optional> // std::optional
#include <functional> // std::function
#include <chrono>

#include "ITaskArgs.hpp"

namespace ilrd
{

class ICommand
{
public:
	virtual ~ICommand() = default;
	virtual std::optional<std::pair<std::function<bool()>,
			std::chrono::milliseconds>> Run(std::shared_ptr<ITaskArgs> taskArgs) = 0;
}; // class ICommand

} // namespace ilrd

#endif //ILRD_RD1645_ICOMMAND_HPP
