
#include "MinionWriteArgs.hpp"
#include "IListener.hpp"

ilrd::MinionWriteArgs::MinionWriteArgs(size_t offset, size_t len,
                                       std::shared_ptr<char[]> data, UID uid)
		: m_offset(offset), m_len(len), m_data(data), m_uid(uid)
{}

size_t ilrd::MinionWriteArgs::GetOffset() const
{
	return m_offset;
}

size_t ilrd::MinionWriteArgs::GetLen() const
{
	return m_len;
}

std::shared_ptr<char[]> ilrd::MinionWriteArgs::GetData()
{
	return m_data;
}

ilrd::UID ilrd::MinionWriteArgs::GetUID()
{
	return m_uid;
}

int ilrd::MinionWriteArgs::GetKey()
{
	return WRITE;
}
