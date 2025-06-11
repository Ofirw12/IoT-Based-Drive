#include <cstring>

#include "WriteMessageSend.hpp"

char* ilrd::WriteMessageSend::AllocAndCpy(std::shared_ptr<const char[]> data, size_t len)
{
	const auto buffer = new char[len]{};
	memcpy(buffer, data.get(), len);
	return buffer;
}

ilrd::WriteMessageSend::WriteMessageSend(const UID& uid, size_t offset, size_t len,
	std::shared_ptr<const char[]> data)
		: AMessage(uid), m_offset(offset), m_len(len), m_data(AllocAndCpy(data, len))
{}

ilrd::WriteMessageSend::WriteMessageSend()
	: AMessage(0), m_offset(), m_len(), m_data(nullptr)
{}

ilrd::WriteMessageSend::~WriteMessageSend()
{
	delete[] m_data;
}

char* ilrd::WriteMessageSend::ToBuffer(char* buffer)
{
	buffer =  AMessage::ToBuffer(buffer);

	*reinterpret_cast<uint32_t*>(buffer) = m_offset;
	buffer += sizeof(uint32_t);

	*reinterpret_cast<uint32_t*>(buffer) = m_len;
	buffer += sizeof(uint32_t);

	memcpy(buffer, m_data, m_len);
	buffer += m_len;

	return buffer;
}

char* ilrd::WriteMessageSend::FromBuffer(char* buffer)
{
	buffer = AMessage::FromBuffer(buffer);

	m_offset = *reinterpret_cast<uint32_t*>(buffer);
	buffer += sizeof(uint32_t);

	m_len = *reinterpret_cast<uint32_t*>(buffer);
	buffer += sizeof(uint32_t);

	const auto newData = new char[m_len];
	memcpy(newData, buffer, m_len);
	delete[] m_data;
	m_data = newData;
	buffer += m_len;

	return buffer;
}

size_t ilrd::WriteMessageSend::GetSize() const
{
	return AMessage::GetSize() + sizeof(m_offset) + sizeof(m_len) + m_len;
}

uint32_t ilrd::WriteMessageSend::GetClassType() const
{
	return WRITE_SEND;
}

size_t ilrd::WriteMessageSend::GetOffset() const
{
	return m_offset;
}

size_t ilrd::WriteMessageSend::GetLength() const
{
	return m_len;
}

char* ilrd::WriteMessageSend::GetData() const
{
	return m_data;
}
