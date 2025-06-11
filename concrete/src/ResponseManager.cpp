
#include "ResponseManager.hpp"

#include <Factory.hpp>

#include "Handleton.hpp"
#include "Logger.hpp"
#include "MinionManager.hpp"
#include "ReadResponse.hpp"
#include "WriteResponse.hpp"

ilrd::ResponseManager::ResponseManager()
	: m_ticketCreateCallback(*this, &ResponseManager::OnTicketCreate),
	  m_ticketDoneCallback(*this, &ResponseManager::OnTicketDone),
	  m_taskCreateCallback(*this, &ResponseManager::OnNewTask),
	  m_nbdProxy(nullptr)
{}

void ilrd::ResponseManager::Init(NBDProxy* nbdProxy)
{
	nbdProxy->RegisterForNewTaskArgs(&m_taskCreateCallback);
	Handleton::GetInstance<MinionManager>()->RegisterForNewTickets(&m_ticketCreateCallback);
	Handleton::GetInstance<Logger>()->Log("ResponseManager Initialized", Logger::DEBUG);
	Handleton::GetInstance<Factory<int, IResponse>>()->Register(READ,
		[]{return new ReadResponse;});
	Handleton::GetInstance<Factory<int, IResponse>>()->Register(WRITE,
	[]{return new WriteResponse;});
	m_nbdProxy = nbdProxy;
}

bool ilrd::ResponseManager::Contains(const UID& uid)
{
	std::unique_lock lock(m_mutex);
	return m_tickets.contains(uid);
}

void ilrd::ResponseManager::Remove(const UID& uid)
{
	std::unique_lock lock(m_mutex);
	m_responses.erase(uid);
	m_tickets.erase(uid);
}

void ilrd::ResponseManager::OnNewTask(const std::shared_ptr<ATaskArgs>& args)
{
	std::string str = "ResponseManager:: New task with uid : " ;
	str.append(std::to_string(args->GetUID().GetUID()));
	Handleton::GetInstance<Logger>()->Log(str, Logger::DEBUG);
	std::unique_lock lock(m_mutex);
	m_responses[args->GetUID()] = Handleton::GetInstance<Factory<int, IResponse>>()->Create(args->GetKey());
}

void ilrd::ResponseManager::OnTicketCreate(const std::shared_ptr<Ticket>& ticket)
{
	std::string str = "ResponseManager:: New ticket with uid : " ;
	str.append(std::to_string(ticket->GetUID().GetUID()));
	Handleton::GetInstance<Logger>()->Log(str, Logger::DEBUG);
	std::unique_lock lock(m_mutex);
		m_tickets[ticket->GetUID()] = ticket;
	lock.unlock();
	ticket->RegisterForTicketResult(&m_ticketDoneCallback);
}

void ilrd::ResponseManager::OnTicketDone(const std::shared_ptr<TaskResult>& res)
{
	std::string str = "ResponseManager:: Done Task with uid : ";
	str.append(std::to_string(res->m_uid.GetUID()));
	std::unique_lock lock(m_mutex);
	m_tickets.erase(res->m_uid);
	m_nbdProxy->NBDSendResponse(*res);
	m_responses.erase(res->m_uid);
}
