
#ifndef ILRD_RD1645_COMMANDWRITE_HPP
#define ILRD_RD1645_COMMANDWRITE_HPP

#include "ICommand.hpp"

namespace ilrd
{

class MasterCommandWrite final : public ICommand
{
public:
 explicit MasterCommandWrite() = default;
 std::optional<std::pair<std::function<bool()>, std::chrono::milliseconds>>
       Run(std::shared_ptr<ITaskArgs> args) override;
}; // class CommandWrite

} // namespace ilrd

#endif //ILRD_RD1645_COMMANDWRITE_HPP
