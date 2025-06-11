#ifndef ILRD_RD1645_TCPSOCKET_HPP
#define ILRD_RD1645_TCPSOCKET_HPP

#include "Socket.hpp"

namespace ilrd
{
class TCPSocket : public Socket
{
public:
    explicit TCPSocket(const std::string& port,const std::string& ip = "",
                        bool server = false); // throw runtime_error
    explicit TCPSocket(int sockfd); // throw runtime_error
    ~TCPSocket() override;
    int GetSocket() const override;

protected:
    void SetSocket(int sockfd);

private:
    int m_socket;
    // sockaddr_in m_server;
};// class TCPSocket
}// namespace ilrd
#endif //ILRD_RD1645_TCPSOCKET_HPP
