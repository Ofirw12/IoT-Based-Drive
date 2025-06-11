
#ifndef ILRD_RD1645_MASTERPROXY_HPP
#define ILRD_RD1645_MASTERPROXY_HPP

#include <memory>
#include <optional>

#include "IInputProxy.hpp"
#include "UDPSocket.hpp"
#include "UID.hpp"

namespace ilrd
{

class MasterProxy final : public IInputProxy
{
public:
	~MasterProxy() override = default;
	MasterProxy(const MasterProxy& other) = delete;
	MasterProxy& operator=(const MasterProxy& other) = delete;
	MasterProxy(MasterProxy&& other) = delete;
	MasterProxy& operator=(MasterProxy&& other) = delete;

	std::shared_ptr<ITaskArgs> GetTaskArgs(int fd, FDMODE mode) override;
	void Init(const std::string& port);
	void SendReadResponse(bool status, std::shared_ptr<char[]> data, size_t len, UID uid);
	void SendWriteResponse(bool status, UID uid);
	[[nodiscard]] int GetSocketFD() const;
private:
	std::optional<UDPSocket> m_socket;
	friend class Handleton;
	explicit MasterProxy() = default;

}; // class MasterProxy

} // namespace ilrd

#endif //ILRD_RD1645_MASTERPROXY_HPP
