
#ifndef ILRD_RD1645_REACTOR_HPP
#define ILRD_RD1645_REACTOR_HPP

#include <functional> // std::function
#include <map> // std::map
#include <memory> // std::unique_ptr

#include "IListener.hpp"

namespace ilrd
{

class Reactor
{
public:
    /// @param listener - default Listener is linux based, do provide an alternative for other OSs
    explicit Reactor(std::unique_ptr<IListener> listener = std::make_unique<LinuxListener>());
    ~Reactor();
    Reactor(const Reactor& other) = delete;
    Reactor& operator=(const Reactor& other) = delete;
    Reactor(Reactor&& other) = delete;
    Reactor& operator=(Reactor&& other) = delete;

    void Register(int fd, FDMODE mode, std::function<void(int, FDMODE)> func);
    void Unregister(int fd, FDMODE mode);
    void Run();
    void Stop();

private:
    bool m_isRunning;
    std::unique_ptr<IListener> m_listener;
    std::map<std::pair<int, FDMODE>, std::function<void(int, FDMODE)>> m_fds;
}; // class Reactor

} // namespace ilrd

#endif //ILRD_RD1645_REACTOR_HPP
