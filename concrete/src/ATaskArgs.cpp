
#include "ATaskArgs.hpp"

ilrd::ATaskArgs::ATaskArgs()
	:m_uid(UID()) {}

ilrd::UID ilrd::ATaskArgs::GetUID()
{
	return m_uid;
}
