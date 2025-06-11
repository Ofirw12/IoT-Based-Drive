
#ifndef ILRD_RD1645_ICOMMAND_HPP
#define ILRD_RD1645_ICOMMAND_HPP

#include <chrono>
#include <functional>
#include <memory>
#include <optional>

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
