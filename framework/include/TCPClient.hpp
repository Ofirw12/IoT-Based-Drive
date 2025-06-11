#ifndef ILRD_RD1645_TCPCLIENT_HPP
#define ILRD_RD1645_TCPCLIENT_HPP

#include "TCPSocket.hpp"

namespace ilrd
{
 class TCPClient : public TCPSocket
 {
 public:
  TCPClient(const std::string& port,const std::string& server_ip="127.0.0.1"); //throws runtime_error
  virtual ~TCPClient();
  int Send(const std::string& str); //throws runtime_error
  int Recv(std::vector<char>* str); //throws runtime_error

 private:
 };// class TCPClient
}// namespace ilrd
#endif //ILRD_RD1645_TCPCLIENT_HPP
