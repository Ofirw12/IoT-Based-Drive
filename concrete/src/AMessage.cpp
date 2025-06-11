
#include "AMessage.hpp"

ilrd::AMessage::AMessage(const UID& uid) : m_uid(uid) {}

ilrd::UID ilrd::AMessage::GetUID()
{
	return m_uid;
}

char* ilrd::AMessage::ToBuffer(char* buffer)
{
	*reinterpret_cast<uint32_t*>(buffer) = GetSize();
	buffer+=sizeof(uint32_t);

	*reinterpret_cast<uint32_t*>(buffer) = GetClassType();
	buffer+=sizeof(uint32_t);

	*reinterpret_cast<UID*>(buffer) = GetUID();
	buffer+=sizeof(UID);

	return buffer;
}

char* ilrd::AMessage::FromBuffer(char* buffer)
{
	m_uid = *reinterpret_cast<UID*>(buffer);
	buffer += sizeof(UID);

	return buffer;
}

size_t ilrd::AMessage::GetSize() const
{
	return sizeof(UID) + 2*sizeof(uint32_t);
}
