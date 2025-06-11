
#include "NBDWriteArgs.hpp"
#include "IListener.hpp"

ilrd::NBDWriteArgs::NBDWriteArgs(const NBDArgs& data)
: m_offset(data.m_offset), m_len(data.m_len), m_buffer(data.m_buffer)
{}

size_t ilrd::NBDWriteArgs::GetOffset() const
{
	return m_offset;
}

size_t ilrd::NBDWriteArgs::GetLen() const
{
	return m_len;
}

std::shared_ptr<const char[]> ilrd::NBDWriteArgs::GetStr() const
{
	return m_buffer;
}

void ilrd::NBDWriteArgs::SetOffset(size_t offset)
{
	m_offset = offset;
}

void ilrd::NBDWriteArgs::SetLen(size_t len)
{
	m_len = len;
}

void ilrd::NBDWriteArgs::SetStr(const std::shared_ptr<const char[]>& buffer)
{
	m_buffer = buffer;
}

int ilrd::NBDWriteArgs::GetKey()
{
	return WRITE;
}
