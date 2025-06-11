
#include "Ticket.hpp"
#include "Handleton.hpp"
#include "Logger.hpp"

ilrd::TaskResult::TaskResult(const UID& uid, Result result,
                             std::shared_ptr<char[]> data, size_t len)
: m_uid(uid), m_result(result), m_data(data), m_len(len)
{}

ilrd::Ticket::Ticket(const UID& uid) : m_uid(uid), m_doneCounter(0) , m_resultSent(false)
{
}

ilrd::UID ilrd::Ticket::GetUID()
{
	return m_uid;
}

void ilrd::Ticket::OnProxyDone(const std::shared_ptr<TaskResult>& res)
{
	if(!m_resultSent)
	{
		std::string str = "Ticket:: Proxy done with uid : " ;
		str.append(std::to_string(res->m_uid.GetUID()));
		Handleton::GetInstance<Logger>()->Log(str, Logger::DEBUG);
		++m_doneCounter;
		if (res->m_data && res->m_result == SUCCESS || m_doneCounter >= 2)
		{
			m_dispatcher.Notify(res);
			m_resultSent = true;
		}
	}
}

void ilrd::Ticket::RegisterForTicketResult(ACallback<const std::shared_ptr<TaskResult>&>* res)
{
	m_dispatcher.Register(res);
}
