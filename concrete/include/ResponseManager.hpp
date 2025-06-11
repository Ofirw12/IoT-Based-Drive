
#ifndef ILRD_RD1645_RESPONSEMANAGER_HPP
#define ILRD_RD1645_RESPONSEMANAGER_HPP

#include <map>
#include <memory>

#include "IResponse.hpp"
#include "NBDProxy.hpp"
#include "Ticket.hpp"
#include "UID.hpp"

namespace ilrd
{

class ResponseManager
{
public:
	ResponseManager();
	void Init(NBDProxy* nbdProxy);
	bool Contains(const UID& uid);
	void Remove(const UID& uid);
private:
	void OnNewTask(const std::shared_ptr<ATaskArgs>& args);
	void OnTicketCreate(const std::shared_ptr<Ticket>& ticket);
	void OnTicketDone(const std::shared_ptr<TaskResult>& res);
	std::map<UID, std::shared_ptr<IResponse>> m_responses;
    std::map<UID, std::shared_ptr<Ticket>> m_tickets;
	Callback<const std::shared_ptr<Ticket>&, ResponseManager> m_ticketCreateCallback;
	Callback<const std::shared_ptr<TaskResult>&, ResponseManager> m_ticketDoneCallback;
	Callback<const std::shared_ptr<ATaskArgs>&, ResponseManager> m_taskCreateCallback;
	NBDProxy* m_nbdProxy;
	std::mutex m_mutex;
}; // class ResponseManager

} // namespace ilrd

#endif //ILRD_RD1645_RESPONSEMANAGER_HPP
