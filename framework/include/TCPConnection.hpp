
#ifndef ILRD_RD1645_TCPCONNECTION_HPP
#define ILRD_RD1645_TCPCONNECTION_HPP

#include <vector>

#include "TCPSocket.hpp"

namespace ilrd
{

class TCPConnection final : public TCPSocket
{
public:
    explicit TCPConnection(int sockfd); //throw runtime_error
    ~TCPConnection() override = default;
    int Send(const std::vector<char>& str) override; //throw runtime_error
    int Recv(std::vector<char>& str) override; //throw runtime_error
};// class TCPConnection

}// namespace ilrd
#endif //ILRD_RD1645_TCPCONNECTION_HPP