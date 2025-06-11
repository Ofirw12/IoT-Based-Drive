
#ifndef ILRD_RD1645_NBDREADARGS_HPP
#define ILRD_RD1645_NBDREADARGS_HPP

#include "ATaskArgs.hpp"

namespace ilrd
{

class NBDReadArgs final : public ATaskArgs
{
public:
	explicit NBDReadArgs(const NBDArgs& data);
	~NBDReadArgs() override = default;
	size_t GetOffset() const;
	size_t GetLen() const;
	void SetOffset(size_t offset);
	void SetLen(size_t len);
	int GetKey() override;
private:
	size_t m_offset;
	size_t m_len;
}; // class NBDReadArgs

} // namespace ilrd

#endif //ILRD_RD1645_NBDREADARGS_HPP
