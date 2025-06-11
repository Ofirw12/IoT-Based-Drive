
#ifndef ILRD_RD1645_TICKET_HPP
#define ILRD_RD1645_TICKET_HPP

#include <memory>

#include "AMessage.hpp"
#include "Dispatcher.hpp"
#include "UID.hpp"

namespace ilrd
{

struct TaskResult
{
	TaskResult(const UID& uid, Result result, std::shared_ptr<char[]> data = nullptr, size_t len = 0);
	UID m_uid;
	Result m_result;
	std::shared_ptr<char[]> m_data;
	size_t m_len;
};

class Ticket
{
public:
	explicit Ticket(const UID& uid);
	UID GetUID();
	void OnProxyDone(const std::shared_ptr<TaskResult>& res);
	void RegisterForTicketResult(ACallback<const std::shared_ptr<TaskResult>&>* res);
private:
    UID m_uid;
	size_t m_doneCounter;
	bool m_resultSent;
	Dispatcher<const std::shared_ptr<TaskResult>&> m_dispatcher;
}; // class Ticket

} // namespace ilrd

#endif //ILRD_RD1645_TICKET_HPP
