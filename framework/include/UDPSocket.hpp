#ifndef ILRD_RD1645_UDPSOCKET_HPP
#define ILRD_RD1645_UDPSOCKET_HPP

#include <vector>
#include <netinet/in.h>

#include "Socket.hpp"

namespace ilrd
{
class UDPSocket final : public Socket
{
public:
    explicit UDPSocket(const std::string& port, const std::string& other_ip = ""); //throw runtime_error
    ~UDPSocket() override;
    int Send(const std::vector<char>& str) override; //throw runtime_error
    int Recv(std::vector<char>& str) override; //throw runtime_error
    void EnableBroadcast() const;
    [[nodiscard]] int GetSocket() const override;

private:
    int m_socket;
    sockaddr_in m_other;
};// class UDPSocket
}// namespace ilrd
#endif //ILRD_RD1645_UDPSOCKET_HPP