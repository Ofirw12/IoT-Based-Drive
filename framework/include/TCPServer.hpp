
#ifndef ILRD_RD1645_TCPSERVER_HPP
#define ILRD_RD1645_TCPSERVER_HPP

#include "TCPConnection.hpp"
#include "TCPSocket.hpp"

namespace ilrd
{
class TCPServer : public TCPSocket
{
public:
    explicit TCPServer(const std::string& port,const std::string& ip=""); //throw runtime_error
    ~TCPServer() override = default;
    [[nodiscard]] TCPConnection Accept() const; //throw runtime_error

private:
    int Send(const std::string& str);
    int Recv(std::vector<char>* str);
};// class TCPServer
}// namespace ilrd
#endif //ILRD_RD1645_TCPSERVER_HPP
