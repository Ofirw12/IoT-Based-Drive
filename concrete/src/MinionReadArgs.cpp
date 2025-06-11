
#include "MinionReadArgs.hpp"
#include "IListener.hpp"

ilrd::MinionReadArgs::MinionReadArgs(size_t offset, size_t len,
                                     std::shared_ptr<char[]> data, UID uid)
		: m_offset(offset), m_len(len), m_data(data), m_uid(uid)
{}

size_t ilrd::MinionReadArgs::GetOffset() const
{
	return m_offset;
}

size_t ilrd::MinionReadArgs::GetLen() const
{
	return m_len;
}

std::shared_ptr<char[]> ilrd::MinionReadArgs::GetData()
{
	return m_data;
}

ilrd::UID ilrd::MinionReadArgs::GetUID()
{
	return m_uid;
}

int ilrd::MinionReadArgs::GetKey()
{
	return READ;
}
