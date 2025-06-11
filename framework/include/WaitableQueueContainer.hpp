
#ifndef ILRD_R1645_WAITABLE_QUEUE_CONTAINER_HPP
#define ILRD_R1645_WAITABLE_QUEUE_CONTAINER_HPP

#include <queue> //std::priority_queue

namespace ilrd
{
template <typename T, typename Q>
class WaitableQueueContainer
{
protected:
    void Push(const T& data);
    void Pop(T& out);
    [[nodiscard]] bool IsEmpty() const;

private:
    Q m_queue;
}; //class WaitableQueueContainer

template <typename T>
class WaitableQueueContainer<T, std::priority_queue<T>>
{
protected:
    void Push(const T& data);
    void Pop(T& out);
    [[nodiscard]] bool IsEmpty() const;

private:
    std::priority_queue<T> m_queue;
}; //class WaitableQueueContainer(for std::priority_queue)

//WaitableQueueContainer Definitions
template<typename T, typename Q>
void WaitableQueueContainer<T, Q>::Push(const T& data)
{
    m_queue.push(data);
}

template <typename T, typename Q>
void WaitableQueueContainer<T, Q>::Pop(T& out)
{
    out = m_queue.front();
    m_queue.pop();
}

template <typename T, typename Q>
bool WaitableQueueContainer<T, Q>::IsEmpty() const
{
    return m_queue.empty();
}

////WaitableQueueContainer(std::priority_queue) Definitions
template <typename T>
void WaitableQueueContainer<T, std::priority_queue<T>>::Push(const T& data)
{
    m_queue.push(data);
}

template <typename T>
void WaitableQueueContainer<T, std::priority_queue<T>>::Pop(T& out)
{
    out = m_queue.top();
    m_queue.pop();
}

template <typename T>
bool WaitableQueueContainer<T, std::priority_queue<T>>::IsEmpty() const
{
    return m_queue.empty();
}

}// namespace ilrd

#endif //ILRD_R1645_WAITABLE_QUEUE_CONTAINER_HPP
