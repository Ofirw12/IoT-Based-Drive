
#include "UID.hpp"

size_t ilrd::UID::m_counter = 1;

ilrd::UID::UID() : m_uid(m_counter++)
{}

ilrd::UID::UID(size_t num): m_uid(0)
{}

ilrd::UID::UID(const UID& other) : m_uid(other.m_uid) {}

size_t ilrd::UID::GetUID() const
{
	return m_uid;
}

bool ilrd::UID::operator<(const UID& other) const
{
	return m_uid < other.m_uid;
}
