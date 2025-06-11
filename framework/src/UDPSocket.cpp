
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "UDPSocket.hpp"


ilrd::UDPSocket::UDPSocket(const std::string& port, const std::string& other_ip)
    : m_socket(-1), m_other()
{
    addrinfo hints = {};
    addrinfo* servinfo = nullptr;
    const addrinfo* p = nullptr;
    int rv = 0;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    if ((rv = getaddrinfo(other_ip.empty() ? NULL :  other_ip.c_str(),
        port.c_str(), &hints, &servinfo)) != 0)
    {
        std::cerr << "getaddrinfo error: " << gai_strerror(rv) << std::endl;
        throw std::runtime_error("getaddrinfo error");
    }

    for (p = servinfo; p != nullptr; p = p->ai_next)
    {
        if ((m_socket = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1)
        {
            std::cerr << "socket error" << std::endl;
            continue;
        }

        if (other_ip.empty() && bind(m_socket, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(m_socket);
            std::cerr << "bind error" << std::endl;
            continue;
        }

        break;
    }

    if (p == nullptr)
    {
        close(m_socket);
        throw std::runtime_error("failed to bind");
    }

    m_other = *reinterpret_cast<sockaddr_in*>(p->ai_addr);
    freeaddrinfo(servinfo);
}

ilrd::UDPSocket::~UDPSocket()
{
    close(m_socket);
}

int ilrd::UDPSocket::Send(const std::vector<char>& str)
{

    const ssize_t bytes = sendto(m_socket, str.data(), str.size() + 1, 0,
          reinterpret_cast<sockaddr*>(&m_other), sizeof(m_other));
    if (bytes == -1)
    {
        throw std::runtime_error("sendto error");
    }

    return bytes;
}

int ilrd::UDPSocket::Recv(std::vector<char>& str)
{
    socklen_t len = sizeof(sockaddr_in);
    char buffer[BUFSIZ] = {0};
    const ssize_t bytes = recvfrom(m_socket, buffer, BUFSIZ, 0,
                    reinterpret_cast<sockaddr*>(&m_other), &len);
    if (bytes == -1)
    {
        throw std::runtime_error("recvfrom error");
    }

    str.resize(bytes);
    memcpy(str.data(), buffer, bytes);

    return bytes;
}

void ilrd::UDPSocket::EnableBroadcast() const
{
    int broadcast_res = 1;
    setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, &broadcast_res, sizeof(int));
}

int ilrd::UDPSocket::GetSocket() const
{
    return m_socket;
}
