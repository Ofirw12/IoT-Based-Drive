#include <csignal>
#include <fcntl.h>
#include <linux/nbd.h>
#include <netinet/in.h>
#include <sys/ioctl.h>

#include "NBD.hpp"
#include "Handleton.hpp"
#include "Logger.hpp"

namespace ilrd
{

#ifdef WORDS_BIGENDIAN
uint64_t Nbd::Ntohll(const uint64_t a_)
{
    return a_;
}
#else
uint64_t Nbd::Ntohll(const uint64_t a_)
{
    uint32_t lo = a_ & 0xffffffff;
    uint32_t hi = a_ >> 32U;
    lo = ntohl(lo);
    hi = ntohl(hi);
    return static_cast<uint64_t>(lo) << 32U | hi;
}
#endif

Nbd::FdWrapper::FdWrapper(const int fd_) : m_fd(fd_)
{
    if (m_fd == -1)
    {
        throw std::runtime_error("File descriptor could not be opened");
    }
}

Nbd::FdWrapper::~FdWrapper()
{
    close(m_fd);
}

Nbd::FdWrapper::operator int() const
{
    return m_fd;
}

void Nbd::NbdClient() const
{
    sigset_t sigset;
    if (sigfillset(&sigset) != 0)
    {
        throw std::runtime_error("sigfillset() failed");
    }

    if (sigprocmask(SIG_SETMASK, &sigset, nullptr) != 0)
    {
        throw std::runtime_error("sigprocmask() failed");
    }

    if (-1 == ioctl(static_cast<int>(m_device), NBD_SET_SOCK, static_cast<int>(m_clientSocket.value())))
    {
        throw std::runtime_error("ioctl() failed");
    }

    if (-1 == ioctl(static_cast<int>(m_device), NBD_DO_IT))
    {
        throw std::runtime_error("ioctl() failed");
    }

    if (-1 == ioctl(static_cast<int>(m_device), NBD_CLEAR_QUE))
    {
        throw std::runtime_error("ioctl() failed");
    }

    if (-1 == ioctl(static_cast<int>(m_device), NBD_CLEAR_SOCK))
    {
        throw std::runtime_error("ioctl() failed");
    }

    exit(EXIT_SUCCESS);
}

void Nbd::InitSockets()
{
    int sockets[2];

    if (0 != socketpair(AF_UNIX, SOCK_STREAM, 0, sockets))
    {
        throw std::runtime_error("socketpair() failed");
    }

    m_serverSocket.emplace(sockets[0]);
    m_clientSocket.emplace(sockets[1]);

    if (-1 == ioctl(static_cast<int>(m_device), NBD_SET_SIZE, SIZE_DRIVE))
    {
        throw std::runtime_error("ioctl() failed");
    }

    if (-1 == ioctl(static_cast<int>(m_device), NBD_CLEAR_SOCK))
    {
        throw std::runtime_error("ioctl() failed");
    }
}

Nbd::Nbd(const std::string& device_) : m_device(open(device_.c_str(), O_RDWR))
{
    InitSockets();

    const pid_t pid = fork();

    if (pid == -1)
    {
        throw std::runtime_error("fork() failed");
    }

    if (pid == 0)
    {
        NbdClient();
    }

    m_nbdDevToDisconnect = static_cast<int>(m_device);
    struct sigaction act{};
    act.sa_handler = DisconnectNbd;
    act.sa_flags = SA_RESTART;

    if (sigemptyset(&act.sa_mask) != 0)
    {
        throw std::runtime_error("sigemptyset() failed");
    }

    if (sigaddset(&act.sa_mask, SIGINT) != 0)
    {
        throw std::runtime_error("sigaddset() failed");
    }

    if (sigaddset(&act.sa_mask, SIGTERM) != 0)
    {
        throw std::runtime_error("sigaddset() failed");
    }

    if (sigaction(SIGINT, &act, nullptr) != 0)
    {
        throw std::runtime_error("sigaction() failed");
    }

    if (sigaction(SIGTERM, &act, nullptr) != 0)
    {
        throw std::runtime_error("sigaction() failed");
    }
}

TCPConnection& Nbd::GetTcpSocket()
{
    return m_serverSocket.value();
}


void Nbd::DisconnectNbd(const int signal_)
{
    (void)signal_;
    if (m_nbdDevToDisconnect != -1)
    {
        if (ioctl(m_nbdDevToDisconnect, NBD_DISCONNECT) == -1)
        {
            Handleton::GetInstance<Logger>()->Log("Failed to request disconnect on nbd device", Logger::WARNING);
        }
        else
        {
            m_nbdDevToDisconnect = -1;
            Handleton::GetInstance<Logger>()->Log("Successfully requested disconnect on nbd device", Logger::WARNING);
        }
    }
}

int Nbd::m_nbdDevToDisconnect = -1;
} // ilrd
