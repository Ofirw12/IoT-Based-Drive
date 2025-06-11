/*******************************************************************************
* FileName: TCPSocket                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: Amir Fragman                                                      *
 * Review Status: APPROVED (26.2.25)                                           *
 ******************************************************************************/
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "TCPSocket.hpp"


ilrd::TCPSocket::TCPSocket(const std::string& port,const std::string& ip, bool server) : m_socket(-1)
{
    addrinfo hints = {};
    addrinfo* servinfo = NULL;
    addrinfo* p = NULL;
    int yes = 1;
    int rv = 0;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((rv = getaddrinfo(ip.empty() ? NULL : ip.c_str(),
            port.c_str(), &hints, &servinfo)) != 0)
    {
        std::cerr << "getaddrinfo: " << gai_strerror(rv) << std::endl;
        throw std::runtime_error("getaddrinfo error");
    }

    for(p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((m_socket = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1)
        {
            std::cerr << (server ? "server: socket" : "client: socket") << std::endl;
            continue;
        }

        if (server)
        {
            if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &yes,
                 sizeof(int)) == -1)
            {
                 std::cerr << "server: setsockopt reuseaddr" << std::endl;
            }

            if (bind(m_socket, p->ai_addr, p->ai_addrlen) == -1)
            {
                 close(m_socket);
                 std::cerr << "server: bind" << std::endl;
                 continue;
            }
        }
        else
        {
            if (connect(m_socket, p->ai_addr, p->ai_addrlen) == -1)
            {
                close(m_socket);
                std::cerr << "client: connect" << std::endl;
                continue;
            }
        }

        break;
    }

    freeaddrinfo(servinfo);

    if (p == NULL)
    {
        std::cerr << (server ? "server: failed to bind": "client: failed to bind") << std::endl;
        throw std::runtime_error("failed to bind");
    }

    if (!server)
    {
        std::cout << "client: connecting to server" << std::endl;
    }
}

ilrd::TCPSocket::TCPSocket(int sockfd) : m_socket(sockfd){}

ilrd::TCPSocket::~TCPSocket()
{
     close(m_socket);
}

int ilrd::TCPSocket::GetSocket() const
{
     return m_socket;
}

void ilrd::TCPSocket::SetSocket(int sockfd)
{
    m_socket = sockfd;
}

