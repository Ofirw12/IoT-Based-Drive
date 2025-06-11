
#ifndef ILRD_RD1645_ITASKARGS_HPP
#define ILRD_RD1645_ITASKARGS_HPP

namespace ilrd
{

class ITaskArgs
{
public:
	virtual ~ITaskArgs() = default;
	virtual int GetKey() = 0;
}; // class ITaskArgs

} // namespace ilrd

#endif //ILRD_RD1645_ITASKARGS_HPP
