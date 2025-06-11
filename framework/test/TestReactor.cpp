
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>

#include "Reactor.hpp"
#include "UDPSocket.hpp"
using namespace ilrd;

int main()
{
    Reactor reactor;
    UDPSocket udp("8080");
    reactor.Register(STDIN_FILENO, READ, [&reactor](int, FDMODE){reactor.Stop();});
    reactor.Register(udp.GetSocket(), READ,
        [&udp](int fd, FDMODE mode)
        {
            static_cast<void>(mode);
            static_cast<void>(fd);
            std::vector<char> bytes;
            udp.Recv(&bytes);
            std::cout << bytes.data() << std::endl;
        });
    reactor.Register(udp.GetSocket(), WRITE,
        [&udp](int fd, FDMODE mode)
        {
            static_cast<void>(mode);
            static_cast<void>(fd);
            udp.Send("You've got message");
            std::cout << "Message sent via udp" << std::endl;
        });

    reactor.Run();
    return 0;
}