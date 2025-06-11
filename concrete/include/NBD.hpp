#ifndef ILRD_RD1645_NBD_HPP
#define ILRD_RD1645_NBD_HPP

#include <optional>

#include "TCPConnection.hpp"

namespace ilrd
{

class Nbd
{
public:
	explicit Nbd(const std::string& device_);
	TCPConnection& GetTcpSocket();
	static uint64_t Ntohll(uint64_t a_);
private:
	class FdWrapper
	{
	public:
		explicit FdWrapper(int fd_);
		~FdWrapper();
		explicit operator int() const;
	private:
		int m_fd;
	};
	FdWrapper m_device;
	std::optional<FdWrapper> m_clientSocket;
	std::optional<TCPConnection> m_serverSocket;
	static int m_nbdDevToDisconnect;
	static void DisconnectNbd(int signal_);
	void NbdClient() const;
	void InitSockets();
	static constexpr uint64_t SIZE_DRIVE = 4 * 1024 * 1024;
};

} // ilrd

#endif //ILRD_RD1645_NBD_HPP
