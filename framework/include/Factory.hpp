
#ifndef ILRD_R1645_FACTORY_HPP
#define ILRD_R1645_FACTORY_HPP

#include <functional> //function
#include <memory> //shared_ptr
#include <unordered_map> //unordered_map

namespace ilrd
{

template <typename KEY, typename BASE, typename... ARGS>
class Factory
{
public:
    void Register(const KEY& key, std::function<BASE*(ARGS...)> func);
    std::shared_ptr<BASE> Create(const KEY& key, const ARGS&... args);
    Factory(const Factory& other) = delete;
    Factory& operator=(const Factory& other) = delete;
private:
    friend class Handleton;
    explicit Factory() = default;
    std::unordered_map<KEY, std::function<BASE*(ARGS...)>> m_map;
}; //class Factory

template <typename KEY, typename BASE, typename... ARGS>
void Factory<KEY, BASE, ARGS...>::Register(const KEY& key,
                                            std::function<BASE*(ARGS...)> func)
{
    m_map[key] = func;
}

template <typename KEY, typename BASE, typename... ARGS>
std::shared_ptr<BASE> Factory<KEY, BASE, ARGS...>::Create(const KEY& key, const ARGS&... args)
{
    return std::shared_ptr<BASE>(m_map.at(key)(args...));
}

}// namespace ilrd
#endif //ILRD_R1645_FACTORY_HPP
