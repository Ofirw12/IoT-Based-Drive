
#ifndef ILRD_RD1645_WAITABLEQUEUE_HPP
#define ILRD_RD1645_WAITABLEQUEUE_HPP

#include <condition_variable> //std::conditional_variable_any
#include <mutex> //std::timed_mutex

#include "WaitableQueueContainer.hpp"

namespace ilrd
{
template <typename T, typename Q = std::queue<T>>
class WaitableQueue : private WaitableQueueContainer<T, Q>
{
public:
    void Push(const T& data);
    void Pop(T& out);
    bool Pop(std::chrono::milliseconds timeout, T& out);
    bool IsEmpty() const;

private:
  mutable std::timed_mutex m_lock;
  std::condition_variable_any m_conditional;

}; // class WaitableQueue


template <typename T, typename Q>
void WaitableQueue<T, Q>::Push(const T& data)
{
    {
        std::unique_lock lock(m_lock);
        WaitableQueueContainer<T, Q>::Push(data);
    }
    m_conditional.notify_one();
}

template <typename T, typename Q>
bool WaitableQueue<T, Q>::Pop(std::chrono::milliseconds timeout, T& out)
{
    const std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::unique_lock lock(m_lock, timeout);
    const std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    const auto wait_time = timeout - (end - start);
    if(end - start > timeout)
    {
        return false;
    }

    if (!m_conditional.wait_for(lock, wait_time,
        [this] {return !WaitableQueueContainer<T, Q>::IsEmpty(); }))
    {
        return false;
    }

    WaitableQueueContainer<T, Q>::Pop(out);
    return true;
}

template <typename T, typename Q>
void WaitableQueue<T, Q>::Pop(T& out)
{
    std::unique_lock lock(m_lock);
    m_conditional.wait(lock,
        [this] {return !WaitableQueueContainer<T, Q>::IsEmpty();});
    WaitableQueueContainer<T, Q>::Pop(out);
}

template <typename T, typename Q>
bool WaitableQueue<T, Q>::IsEmpty() const
{
    std::unique_lock lock(m_lock);
    return WaitableQueueContainer<T, Q>::IsEmpty();
}

}// namespace ilrd
#endif //ILRD_RD1645_WAITABLEQUEUE_HPP
