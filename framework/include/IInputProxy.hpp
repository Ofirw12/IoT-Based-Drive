
#ifndef ILRD_RD1645_IINPUTPROXY_HPP
#define ILRD_RD1645_IINPUTPROXY_HPP

#include "IListener.hpp"
#include "ITaskArgs.hpp"

namespace ilrd
{

class IInputProxy
{
public:
	virtual ~IInputProxy() = default;
	virtual std::shared_ptr<ITaskArgs> GetTaskArgs(int fd, FDMODE mode) = 0;
}; // class IInputProxy

} // namespace ilrd

#endif //ILRD_RD1645_IINPUTPROXY_HPP
