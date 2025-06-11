/*******************************************************************************
* FileName: TCPConnection                                                      *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: Amir Fragman                                                      *
 * Review Status: APPROVED (26.2.25)                                           *
 ******************************************************************************/
#include "TCPConnection.hpp"

#include <unistd.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>

ilrd::TCPConnection::TCPConnection(int sockfd): TCPSocket(sockfd) {}

ilrd::TCPConnection::~TCPConnection() {}

int ilrd::TCPConnection::Send(const std::vector<char>& str)
{
    ssize_t bytesSent = 0;

    while (bytesSent < str.size())
    {
        const ssize_t sent = send(GetSocket(), str.data() + bytesSent,
                                            str.size() - bytesSent, 0);
        if (sent <= 0)
        {
            throw std::runtime_error("server: failed to send");
        }
        bytesSent += sent;
    }

    return bytesSent;
}

int ilrd::TCPConnection::Recv(std::vector<char>& str)
{
    ssize_t bytesReceived = 0;
    while(bytesReceived < str.size())
    {
        bytesReceived += recv(GetSocket(), str.data() + bytesReceived,
                                        str.size() - bytesReceived, 0);
        if (bytesReceived <= 0)
        {
            throw std::runtime_error("server: recv error");
        }
    }

    return bytesReceived;
}

