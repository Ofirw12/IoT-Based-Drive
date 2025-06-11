
#ifndef ILRD_RD1645_COMMANDREAD_HPP
#define ILRD_RD1645_COMMANDREAD_HPP

#include "ICommand.hpp"
#include "NBDReadArgs.hpp"

namespace ilrd
{

class MasterCommandRead final : public ICommand
{
public:
 explicit MasterCommandRead() = default;
 std::optional<std::pair<std::function<bool()>, std::chrono::milliseconds>>
       Run(std::shared_ptr<ITaskArgs> args) override;
}; // class CommandRead

} // namespace ilrd

#endif //ILRD_RD1645_COMMANDREAD_HPP
