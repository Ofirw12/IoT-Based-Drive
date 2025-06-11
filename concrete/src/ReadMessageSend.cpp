
#include "ReadMessageSend.hpp"

ilrd::ReadMessageSend::ReadMessageSend(const UID& uid, size_t offset,
	size_t len): AMessage(uid), m_offset(offset), m_len(len)
{}

ilrd::ReadMessageSend::ReadMessageSend() : AMessage(0), m_offset(), m_len()
{}

char* ilrd::ReadMessageSend::ToBuffer(char* buffer)
{
	buffer = AMessage::ToBuffer(buffer);

	*reinterpret_cast<uint32_t*>(buffer) += m_offset;
	buffer += sizeof(uint32_t);

	*reinterpret_cast<uint32_t*>(buffer) += m_len;
	buffer += sizeof(uint32_t);

	return buffer;
}

char* ilrd::ReadMessageSend::FromBuffer(char* buffer)
{
	buffer = AMessage::FromBuffer(buffer);

	m_offset = *reinterpret_cast<uint32_t*>(buffer);
	buffer += sizeof(uint32_t);

	m_len = *reinterpret_cast<uint32_t*>(buffer);
	buffer += sizeof(uint32_t);

	return buffer;
}

size_t ilrd::ReadMessageSend::GetSize() const
{
	return AMessage::GetSize() + sizeof(m_offset) + sizeof(m_len);
}

uint32_t ilrd::ReadMessageSend::GetClassType() const
{
	return READ_SEND;
}

size_t ilrd::ReadMessageSend::GetOffset() const
{
	return m_offset;
}

size_t ilrd::ReadMessageSend::GetLength() const
{
	return m_len;
}
