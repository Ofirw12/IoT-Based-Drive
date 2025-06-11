/*******************************************************************************
* FileName: TCPClient                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: Amir Fragman                                                      *
 * Review Status: APPROVED (26.2.25)                                           *
 ******************************************************************************/

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "TCPClient.hpp"

ilrd::TCPClient::TCPClient(const std::string& port, const std::string& server_ip)
    : TCPSocket(port, server_ip, false) {}

ilrd::TCPClient::~TCPClient() {}

int ilrd::TCPClient::Send(const std::string& str)
{
    ssize_t bytes = send(GetSocket(), str.c_str(), str.length() + 1, 0);
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
    ssize_t bytes = recv(GetSocket(), buffer, sizeof(buffer), 0);
    if (bytes == -1)
    {
        std::cerr << "client: recv" << std::endl;
        throw std::runtime_error("client: recv failed");
    }

    str->resize(bytes);
    memcpy(str->data(), buffer, bytes);
    return 0;
}
