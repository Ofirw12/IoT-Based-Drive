
#ifndef ILRD_RD1645_NBDWRITEARGS_HPP
#define ILRD_RD1645_NBDWRITEARGS_HPP

#include <memory>

#include "ATaskArgs.hpp"

namespace ilrd
{

class NBDWriteArgs final : public ATaskArgs
{
public:
	NBDWriteArgs(const NBDArgs& data);
	~NBDWriteArgs() override = default;
	size_t GetOffset() const;
	size_t GetLen() const;
	std::shared_ptr<const char[]> GetStr() const;
	void SetOffset(size_t offset);
	void SetLen(size_t len);
	void SetStr(const std::shared_ptr<const char[]>& buffer);
	int GetKey() override;
private:
	size_t m_offset;
	size_t m_len;
	std::shared_ptr<const char[]> m_buffer;
}; // class NBDWriteArgs

} // namespace ilrd

#endif //ILRD_RD1645_NBDWRITEARGS_HPP
