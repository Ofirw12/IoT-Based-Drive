//
// Created by ofir on 4/6/25.
//

#include "NBDReadArgs.hpp"
#include "IListener.hpp"

ilrd::NBDReadArgs::NBDReadArgs(const NBDArgs& data)
  : m_offset(data.m_offset), m_len(data.m_len)
{ }

size_t ilrd::NBDReadArgs::GetOffset() const
{
    return m_offset;
}

size_t ilrd::NBDReadArgs::GetLen() const
{
	return m_len;
}

void ilrd::NBDReadArgs::SetOffset(size_t offset)
{
	m_offset = offset;
}

void ilrd::NBDReadArgs::SetLen(size_t len)
{
	m_len = len;
}

int ilrd::NBDReadArgs::GetKey()
{
	return READ;
}
