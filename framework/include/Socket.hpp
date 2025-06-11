#ifndef ILRD_RD1645_SOCKET_HPP
#define ILRD_RD1645_SOCKET_HPP

#include <string>
#include <vector>

namespace ilrd
{
class Socket
{
public:
    virtual ~Socket() = default;
    virtual int Send(const std::vector<char>& str) = 0;
    virtual int Recv(std::vector<char>& str) = 0;
    [[nodiscard]] virtual int GetSocket() const = 0;
};// class Socket
}// namespace ilrd

#endif //ILRD_RD1645_SOCKET_HPP