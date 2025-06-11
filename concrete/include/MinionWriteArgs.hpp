
#ifndef ILRD_RD1645_MINIONWRITEARGS_HPP
#define ILRD_RD1645_MINIONWRITEARGS_HPP

#include <memory>

#include "ITaskArgs.hpp"
#include "UID.hpp"

namespace ilrd
{

class MinionWriteArgs final : public ITaskArgs
{
public:
	explicit MinionWriteArgs(size_t offset, size_t len, std::shared_ptr<char[]> data, UID uid);
	size_t GetOffset() const;
	size_t GetLen() const;
	std::shared_ptr<char[]> GetData();
	UID GetUID();
	int GetKey() override;
private:
    size_t m_offset;
	size_t m_len;
	std::shared_ptr<char[]> m_data;
	UID m_uid;
}; // class MinionWriteArgs

} // namespace ilrd

#endif //ILRD_RD1645_MINIONWRITEARGS_HPP
