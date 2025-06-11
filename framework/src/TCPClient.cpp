
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>

#include "TCPClient.hpp"

ilrd::TCPClient::TCPClient(const std::string& port, const std::string& server_ip)
    : TCPSocket(port, server_ip, false) {}

int ilrd::TCPClient::Send(const std::string& str) const
{
    const ssize_t bytes = send(GetSocket(), str.c_str(), str.length() + 1, 0);
    if (bytes == -1)
    {
        std::cerr << "client: send" << std::endl;
        throw std::runtime_error("client: send failed");
    }

    return bytes;
}

int ilrd::TCPClient::Recv(std::vector<char>* str)
{
    char buffer[1024] = {0};
    const ssize_t bytes = recv(GetSocket(), buffer, sizeof(buffer), 0);
    if (bytes == -1)
    {
        std::cerr << "client: recv" << std::endl;
        throw std::runtime_error("client: recv failed");
    }

    str->resize(bytes);
    memcpy(str->data(), buffer, bytes);
    return 0;
}
