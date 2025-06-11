
#ifndef ILRD_RD1645_MINIONPROXY_HPP
#define ILRD_RD1645_MINIONPROXY_HPP

#include <map>

#include "IMinionProxy.hpp"
#include "Ticket.hpp"
#include "UDPSocket.hpp"

namespace ilrd
{

class MinionProxy final : public IMinionProxy
{
public:
	explicit MinionProxy(const std::string& send_port, const std::string& to_ip);
    void AddReadTask(size_t offset, size_t length, std::function<void(const std::shared_ptr<TaskResult>&)> onDone, const UID& uid) override;
	void AddWriteTask(size_t offset, size_t length, std::shared_ptr<const char[]> data, std::function<void(const std::shared_ptr<TaskResult>&)> onDone, const UID& uid) override;
	int GetMinionFD() override;
	void OnMinionWakeup() override;
private:
	UDPSocket m_socket;
	std::map<UID, std::function<void(const std::shared_ptr<TaskResult>&)>> m_OnDone;
	std::mutex m_mutex;

}; // class MinionProxy

} // namespace ilrd

#endif //ILRD_RD1645_MINIONPROXY_HPP
