
#include "ReadMessageResponse.hpp"

#include <cstring>

char* ilrd::ReadMessageResponse::AllocAndCpy(std::shared_ptr<const char[]> data, size_t len)
{
	const auto buffer = new char[len]{};
	memcpy(buffer, data.get(), len);
	return buffer;
}

ilrd::ReadMessageResponse::ReadMessageResponse()
	: AMessage(0), m_len(0), m_data(nullptr), m_res()
{}

ilrd::ReadMessageResponse::ReadMessageResponse(const UID& uid,
					std::shared_ptr<const char[]> data, size_t len, Result res)
	: AMessage(uid), m_len(len),
		m_data(AllocAndCpy(data, len)), m_res(res)
{}

ilrd::ReadMessageResponse::~ReadMessageResponse()
{
	delete[] m_data;
}

char* ilrd::ReadMessageResponse::ToBuffer(char* buffer)
{
	buffer = AMessage::ToBuffer(buffer);

	*reinterpret_cast<uint32_t*>(buffer) = m_len;
	buffer += sizeof(uint32_t);

	memcpy(buffer, m_data, m_len);
	buffer += m_len;

	*reinterpret_cast<Result*>(buffer) = GetResult();
	buffer+=sizeof(Result);

	return buffer;
}

char* ilrd::ReadMessageResponse::FromBuffer(char* buffer)
{
	buffer = AMessage::FromBuffer(buffer);

	m_len = *reinterpret_cast<uint32_t*>(buffer);
	buffer += sizeof(uint32_t);

	const auto newData = new char[m_len]{};
	memcpy(newData, buffer, m_len);
	delete[] m_data;
	m_data = newData;
	buffer += m_len;

	m_res = *reinterpret_cast<Result*>(buffer);
	buffer+=sizeof(Result);

	return buffer;
}

size_t ilrd::ReadMessageResponse::GetSize() const
{
	return AMessage::GetSize() + sizeof(Result) + sizeof(m_len) + m_len;
}

uint32_t ilrd::ReadMessageResponse::GetClassType() const
{
	return READ_RESPONSE;
}

ilrd::Result ilrd::ReadMessageResponse::GetResult() const
{
	return m_res;
}

char* ilrd::ReadMessageResponse::GetData() const
{
	return m_data;
}

size_t ilrd::ReadMessageResponse::GetLen() const
{
	return m_len;
}
