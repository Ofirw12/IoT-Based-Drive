#ifndef ILRD_RD1645_TCPSERVER_HPP
#define ILRD_RD1645_TCPSERVER_HPP

#include "TCPSocket.hpp"
#include "TCPConnection.hpp"

namespace ilrd
{
class TCPServer : public TCPSocket
{
public:
    TCPServer(const std::string& port,const std::string& ip=""); //throw runtime_error
    virtual ~TCPServer();
    TCPConnection Accept() const; //throw runtime_error

private:
    int Send(const std::string& str);
    int Recv(std::vector<char>* str);
};// class TCPServer
}// namespace ilrd
#endif //ILRD_RD1645_TCPSERVER_HPP
