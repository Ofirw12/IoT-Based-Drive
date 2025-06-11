/*******************************************************************************
* FileName: TCPServer                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: Amir Fragman                                                      *
 * Review Status: APPROVED (26.2.25)                                           *
 ******************************************************************************/

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>

#include "TCPServer.hpp"

ilrd::TCPServer::TCPServer(const std::string& port, const std::string& ip)
    : TCPSocket(port, ip, true)
{
    const int max_clients = 20;

    if (listen(GetSocket(), max_clients) == -1)
    {
        std::cerr << "server: listen" << std::endl;
        throw std::runtime_error("server: listen");
    }
}

ilrd::TCPServer::~TCPServer() {}


int ilrd::TCPServer::Send(const std::string& str)
{
    return 0;
}

int ilrd::TCPServer::Recv(std::vector<char>* str)
{
    return 0;
}

ilrd::TCPConnection ilrd::TCPServer::Accept() const
{
    sockaddr_storage their_addr = {};
    socklen_t sin_size = {};
    int new_fd = 0;
    std::cout << "server: waiting for connections" << std::endl;
    new_fd = accept(GetSocket(), reinterpret_cast<sockaddr*>(&their_addr),
                                                                &sin_size);
    if (new_fd == -1)
    {
        throw std::runtime_error("server: accept");
    }

    return TCPConnection(new_fd);
}
