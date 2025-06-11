
#include "MinionManager.hpp"

#include <Factory.hpp>

#include "Handleton.hpp"
#include "Logger.hpp"
#include "MinionProxy.hpp"
#include "NBDReadArgs.hpp"
#include "NBDWriteArgs.hpp"
#include "ReadMessageResponse.hpp"
#include "ReadMessageSend.hpp"
#include "WriteMessageResponse.hpp"
#include "WriteMessageSend.hpp"

ilrd::MinionManager::MinionManager(): m_devSize(0) {}

ilrd::MinionManager::~MinionManager()
{
	m_reactor.Stop();
}

void ilrd::MinionManager::AddWriteTask(size_t offset, size_t len,
	const UID& uid, const std::shared_ptr<const char[]>& buffer)
{
	auto ticket = std::make_shared<Ticket>(uid);
	m_dispatcher.Notify(ticket);

	const size_t minion_relative_offset = offset % m_devSize;
	const size_t minion_index = offset / m_devSize;
	const size_t backup_relative_offset = offset + (m_devSize/2);
	const size_t backup_index = (minion_index + 1) % m_minions.size();

	std::unique_lock lock(m_mutex);
	m_minions[minion_index]->AddWriteTask(minion_relative_offset, len, buffer,
		[ticket](const std::shared_ptr<TaskResult>& res){ ticket->OnProxyDone(res);}, uid);
	m_minions[backup_index]->AddWriteTask(backup_relative_offset, len, buffer,
	[ticket](const std::shared_ptr<TaskResult>& res){ ticket->OnProxyDone(res);}, uid);
}

void ilrd::MinionManager::AddReadTask(size_t offset, size_t len, const UID& uid)
{
	auto ticket = std::make_shared<Ticket>(uid);
	m_dispatcher.Notify(ticket);

	const size_t minion_relative_offset = offset % m_devSize;
	const size_t minion_index = offset / m_devSize;
	const size_t backup_relative_offset = offset + (m_devSize/2);
	const size_t backup_index = (minion_index + 1) % m_minions.size();

	std::unique_lock lock(m_mutex);
	m_minions[minion_index]->AddReadTask(minion_relative_offset, len,
		[ticket](const std::shared_ptr<TaskResult>& msg){ ticket->OnProxyDone(msg);}, uid);
	m_minions[backup_index]->AddReadTask(backup_relative_offset, len,
	[ticket](const std::shared_ptr<TaskResult>& msg){ ticket->OnProxyDone(msg);}, uid);
}

void ilrd::MinionManager::RegisterForNewTickets(ACallback<const std::shared_ptr<Ticket>&>* callback)
{
	m_dispatcher.Register(callback);
}

void ilrd::MinionManager::Init(size_t mb_forEach,
	std::vector<std::shared_ptr<IMinionProxy>> minions)
{
	m_devSize = mb_forEach;
	m_minions.reserve(minions.size());
	m_minions.insert(m_minions.begin(), minions.begin(), minions.end());
	for(size_t i = 0; i < minions.size() ; ++i)
	{
		m_reactor.Register(m_minions[i]->GetMinionFD(), READ, [this, i](int fd, FDMODE mode)
		{
			m_minions[i]->OnMinionWakeup();
		});
	}
	Handleton::GetInstance<Factory<int, AMessage>>()->Register(WRITE_SEND, []{return new WriteMessageSend;});
	Handleton::GetInstance<Factory<int, AMessage>>()->Register(WRITE_RESPONSE, []{return new WriteMessageResponse;});
	Handleton::GetInstance<Factory<int, AMessage>>()->Register(READ_SEND, []{return new ReadMessageSend;});
	Handleton::GetInstance<Factory<int, AMessage>>()->Register(READ_RESPONSE, []{return new ReadMessageResponse;});

	m_thread = std::jthread([this]{m_reactor.Run();});
}
