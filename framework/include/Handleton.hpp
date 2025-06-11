
#ifndef ILRD_R1645_HANDLETON_HPP
#define ILRD_R1645_HANDLETON_HPP

#include <memory> // std::shared_ptr
#include <mutex> // std::mutex
#include <unordered_map> // std::unordered_map

namespace ilrd
{
class Handleton
{
public:
    template <typename T>
    static T* GetInstance();
private:
    Handleton() = delete;
    ~Handleton() = delete;
    Handleton(const Handleton&) = delete;
    Handleton& operator=(const Handleton&) = delete;

    class HashFunction
    {
    public:
        size_t operator()(const std::type_info* type) const
        {
            return type->hash_code();
        }
    };

    class EqualFunction
    {
    public:
        bool operator()(const std::type_info* lhs, const std::type_info* rhs) const
        {
            return *lhs == *rhs;
        }
    };

    static std::unordered_map<const std::type_info*, std::shared_ptr<void>,
                HashFunction, EqualFunction> m_instances;
    static std::mutex m_mutex;

};

// template <typename T>
// std::mutex Handleton::m_mutex;

template <typename T>
T* Handleton::GetInstance()
{
    /*
    DCLP Method (not perfect: race condition of m_instances):
    std::atomic_thread_fence(std::memory_order_acquire);
    if (!m_instances.contains(&typeid(T)))
    {
        std::unique_lock lock(m_mutex<T>);
        std::atomic_thread_fence(std::memory_order_acquire);
        if (!m_instances.contains(&typeid(T)))
        {
            std::shared_ptr<T> temp = std::make_shared<T>();
            std::atomic_thread_fence(std::memory_order_release);
            m_instances[&typeid(T)] = temp;
        }
    }
     */

    /* Option 2 std DCLP method */

    static std::once_flag flag;
    std::call_once(flag, []
    {
        std::unique_lock lock(m_mutex);
        if (!m_instances.contains(&typeid(T)))
        {
            m_instances[&typeid(T)].reset(new T);
        }
    });

    // option 3: mutex but its overkill
    // std::unique_lock<std::mutex> lock(m_mutex<T>);
    // if (!m_instances.contains(&typeid(T)))
    // {
    //     m_instances[&typeid(T)].reset(new T);
    // }

    return static_cast<T*>(m_instances.at(&typeid(T)).get());
}

} // namespace ilrd

#endif //ILRD_R1645_HANDLETON_HPP
