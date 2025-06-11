
#include <utility>
#include <ranges>
#include "Reactor.hpp"

ilrd::Reactor::Reactor(std::unique_ptr<IListener> listener)
: m_isRunning(false)
{
    m_listener.swap(listener);
}

ilrd::Reactor::~Reactor()
{
    Stop();
}

void ilrd::Reactor::Register(int fd, FDMODE mode,
                             std::function<void(int, FDMODE)> func)
{
    m_fds[{fd,mode}] = std::move(func);
}

void ilrd::Reactor::Unregister(int fd, FDMODE mode)
{
    try
    {
        m_fds.erase({fd,mode});
    }
    catch (...) {}
}

void ilrd::Reactor::Run()
{
    m_isRunning = true;
    while(m_isRunning)
    {
        std::vector<std::pair<int, FDMODE>> vec;
        vec.reserve(m_fds.size());
        for(const auto key : m_fds | std::views::keys)
        {
            vec.emplace_back(key);
        }

        for (std::vector<std::pair<int, FDMODE>> vec2 = m_listener->Listen(vec); auto pair : vec2)
        {
            std::apply(m_fds[pair], pair);
        }
    }
}

void ilrd::Reactor::Stop()
{
    m_isRunning = false;
}
