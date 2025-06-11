
#include "WriteMessageResponse.hpp"

ilrd::WriteMessageResponse::WriteMessageResponse(const UID& uid, Result res)
	:AMessage(uid), m_res(res)
{}

ilrd::WriteMessageResponse::WriteMessageResponse()
	: AMessage(0), m_res()
{}

char* ilrd::WriteMessageResponse::ToBuffer(char* buffer)
{
	buffer = AMessage::ToBuffer(buffer);

	*reinterpret_cast<Result*>(buffer) = GetResult();
	buffer+=sizeof(Result);

	return buffer;
}

char* ilrd::WriteMessageResponse::FromBuffer(char* buffer)
{
	buffer = AMessage::FromBuffer(buffer);

	m_res = *reinterpret_cast<Result*>(buffer);
	buffer+=sizeof(Result);

	return buffer;
}

size_t ilrd::WriteMessageResponse::GetSize() const
{
	return AMessage::GetSize() + sizeof(Result);
}

uint32_t ilrd::WriteMessageResponse::GetClassType() const
{
	return WRITE_RESPONSE;
}

ilrd::Result ilrd::WriteMessageResponse::GetResult() const
{
	return m_res;
}
