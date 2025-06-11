/*******************************************************************************
* FileName: Singleton                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: Amit Yehezkel                                                     *
 * Review Status: APPROVED (17.3.25)                                           *
 ******************************************************************************/
#ifndef ILRD_R1645_SINGLETON_HPP
#define ILRD_R1645_SINGLETON_HPP

#include <mutex> // std::mutex

namespace ilrd
{
template<typename T>
class Singleton
{
public:
    static T* GetInstance();

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton() = delete;
    ~Singleton() = delete;
private:
    static void Destruct();

    static std::atomic<T*> m_Instance;
    static std::atomic_bool m_destroyed;
    static std::mutex m_mutex;
}; //class Singleton

template <typename T>
std::atomic<T*> Singleton<T>::m_Instance = nullptr;

template <typename T>
std::atomic_bool Singleton<T>::m_destroyed = false;

template <typename T>
std::mutex Singleton<T>::m_mutex;

template <typename T>
T* Singleton<T>::GetInstance()
{
    if (m_destroyed.load(std::memory_order_relaxed))
    {
        throw std::runtime_error("Single instance is already destroyed");
    }

    T* tmp = m_Instance.load(std::memory_order_acquire);
    if (tmp == nullptr)
    {
        std::unique_lock m_lock(m_mutex);
        tmp = m_Instance.load(std::memory_order_relaxed);
        if (tmp == nullptr)
        {
            tmp = new T();
            m_Instance.store(tmp, std::memory_order_release);
            std::atexit(Destruct);
        }
    }
    return m_Instance;
}

template <typename T>
void Singleton<T>::Destruct()
{
    m_destroyed.store(true);
    delete m_Instance.load();
    m_Instance.store(nullptr);
}

}// namespace ilrd

#endif //ILRD_R1645_SINGLETON_HPP


