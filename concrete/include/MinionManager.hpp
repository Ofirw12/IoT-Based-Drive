
#ifndef ILRD_RD1645_MINIONMANAGER_HPP
#define ILRD_RD1645_MINIONMANAGER_HPP

#include <thread>

// #include "ATaskArgs.hpp"
#include "IMinionProxy.hpp"
#include "Reactor.hpp"
#include "Ticket.hpp"

namespace ilrd
{

class MinionManager
{
public:
	~MinionManager();
	void AddWriteTask(size_t offset, size_t len, const UID& uid, const std::shared_ptr<const char[]>& buffer = nullptr);
	void AddReadTask(size_t offset, size_t len, const UID& uid);
	void RegisterForNewTickets(ACallback<const std::shared_ptr<Ticket>&>* callback);
	void Init(size_t mb_forEach, std::vector<std::shared_ptr<IMinionProxy>> minions);
private:
	friend class Handleton;
    explicit MinionManager();
	size_t m_devSize;
	std::vector<std::shared_ptr<IMinionProxy>> m_minions;
	Dispatcher<const std::shared_ptr<Ticket>&> m_dispatcher;
	Reactor m_reactor;
	std::jthread m_thread;
	std::mutex m_mutex;

}; // class MinionManager

} // namespace ilrd

#endif //ILRD_RD1645_MINIONMANAGER_HPP
