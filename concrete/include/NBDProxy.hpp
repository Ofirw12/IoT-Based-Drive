
#ifndef ILRD_RD1645_NBDPROXY_HPP
#define ILRD_RD1645_NBDPROXY_HPP

#include <map>
#include <memory>

#include "ATaskArgs.hpp"
#include "Dispatcher.hpp"
#include "IInputProxy.hpp"
#include "NBD.hpp"
#include "Ticket.hpp"

namespace ilrd
{

class NBDProxy final : public IInputProxy
{
public:
	explicit NBDProxy(Nbd& nbd);
	~NBDProxy() override = default;
	std::shared_ptr<ITaskArgs> GetTaskArgs(int fd, FDMODE mode) override;
	void RegisterForNewTaskArgs(ACallback<const std::shared_ptr<ATaskArgs>&>* callback);
	void NBDSendResponse(const TaskResult& taskRes);

private:
	Dispatcher<const std::shared_ptr<ATaskArgs>&> m_dispatcher;
	std::map<UID, nbd_reply> m_replies;
	Nbd& m_nbd;
	std::mutex m_mutex;
}; // class NBDProxy

} // namespace ilrd

#endif //ILRD_RD1645_NBDPROXY_HPP
