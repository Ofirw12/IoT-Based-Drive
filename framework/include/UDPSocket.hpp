#ifndef ILRD_RD1645_UDPSOCKET_HPP
#define ILRD_RD1645_UDPSOCKET_HPP

#include <netinet/in.h>
#include <vector>
#include "Socket.hpp"

namespace ilrd
{
class UDPSocket : public Socket
{
public:
    UDPSocket(const std::string& port, const std::string& other_ip = ""); //throw runtime_error
    ~UDPSocket();
    int Send(const std::vector<char>& str); //throw runtime_error
    int Recv(std::vector<char>& str); //throw runtime_error
    void EnableBroadcast() const;
    int GetSocket() const;

private:
    int m_socket;
    sockaddr_in m_other;
};// class UDPSocket
}// namespace ilrd
#endif //ILRD_RD1645_UDPSOCKET_HPP