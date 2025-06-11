/*******************************************************************************
* FileName: Dispatcher                                                         *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: Sahar  Moalem                                                     *
 * Review Status: APPROVED (18/3/25)                                           *
 ******************************************************************************/

#ifndef ILRD_RD1645_DISPATCHER_HPP
#define ILRD_RD1645_DISPATCHER_HPP
#include <unordered_set> // std::unordered_set
#include <queue> // std::queue

namespace ilrd
{

template< typename EVENT>
class ACallback;

template <typename EVENT>
class Dispatcher
{
public:
    Dispatcher() = default;
    ~Dispatcher();
    Dispatcher(const Dispatcher&) = delete;
    Dispatcher& operator=(const Dispatcher&) = delete;

    void Register(ACallback<EVENT>* callback);
    void Unregister(ACallback<EVENT>* callback);
    void Notify(const EVENT& event);
private:
    void UpdateSet();
    std::unordered_set<ACallback<EVENT>*> m_callbacks;
    std::queue<std::pair<ACallback<EVENT>*, bool>> m_actions;
}; // class Dispatcher


template <typename EVENT>
class ACallback
{
public:
    ACallback() = default;
    virtual void Notify(const EVENT& event) = 0;
    virtual void NotifyDeath() = 0;
    void SetDispatcher(Dispatcher<EVENT>* dispatcher);
    virtual ~ACallback();
private:
    Dispatcher<EVENT>* m_dispatcher;
}; // class ACallback

template <typename EVENT, typename OBJ>
class Callback : public ACallback<EVENT>
{
public:
    Callback(OBJ& obj, void(OBJ::*notify_func)(EVENT),
             void(OBJ::*death_func)() = nullptr);
    ~Callback() = default;
private:
    void Notify(const EVENT& event) override;
    void NotifyDeath() override;
    OBJ& m_obj;
    void (OBJ::*m_notifyFunc)(EVENT);
    void (OBJ::*m_deathFunc)();

}; //class Callback

template <typename EVENT>
Dispatcher<EVENT>::~Dispatcher()
{
    UpdateSet();
    for (ACallback<EVENT>* callback : m_callbacks)
    {
        try
        {
            callback->NotifyDeath();
        }
        catch (...) {}
    }
}

template <typename EVENT>
void Dispatcher<EVENT>::Register(ACallback<EVENT>* callback)
{
    m_actions.push({callback, true});
    callback->SetDispatcher(this);
}

template <typename EVENT>
void Dispatcher<EVENT>::Unregister(ACallback<EVENT>* callback)
{
    m_actions.push({callback, false});
    callback->SetDispatcher(nullptr);
}

template <typename EVENT>
void Dispatcher<EVENT>::Notify(const EVENT& event)
{
    UpdateSet();

    for (ACallback<EVENT>* callback : m_callbacks)
    {
        callback->Notify(event);
    }
}

template <typename EVENT>
void Dispatcher<EVENT>::UpdateSet()
{
    while(!m_actions.empty())
    {
        std::pair<ACallback<EVENT>*, bool> pair = m_actions.front();
        m_actions.pop();
        if (pair.second == true)
        {
            m_callbacks.insert(pair.first);
        }
        else
        {
            m_callbacks.erase(pair.first);
        }
    }
}

template <typename EVENT>
void ACallback<EVENT>::SetDispatcher(Dispatcher<EVENT>* dispatcher)
{
    m_dispatcher = dispatcher;
}

template <typename EVENT>
ACallback<EVENT>::~ACallback()
{
    if (m_dispatcher)
    {
        m_dispatcher->Unregister(this);
    }
}

template <typename EVENT, typename OBJ>
Callback<EVENT, OBJ>::Callback(OBJ& obj, void(OBJ::*notify_func)(EVENT),
                                void(OBJ::*death_func)())
        : ACallback<EVENT>(), m_obj(obj), m_notifyFunc(notify_func),
                                        m_deathFunc(death_func)
{}

template <typename EVENT, typename OBJ>
void Callback<EVENT, OBJ>::Notify(const EVENT& event)
{
    (m_obj.*m_notifyFunc)(event);
}

template <typename EVENT, typename OBJ>
void Callback<EVENT, OBJ>::NotifyDeath()
{
    if (m_deathFunc)
    {
        (m_obj.*m_deathFunc)();
    }
}

} // namespace ilrd

#endif //ILRD_RD1645_DISPATCHER_HPP
