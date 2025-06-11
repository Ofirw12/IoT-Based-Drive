/*******************************************************************************
* FileName: ITPTask                                                            *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: Amit Yehezkel                                                     *
 * Review Status: APPROVED (12.3.25)                                           *
 ******************************************************************************/
#ifndef ILRD_R1645_ITPTASK_HPP
#define ILRD_R1645_ITPTASK_HPP

#include <functional> // std::function
#include <semaphore> // std::binary_semaphore

namespace ilrd::threadpool
{

class ITPTask
{
public:
    virtual void Run() = 0;

protected:
    virtual ~ITPTask() = default;
}; //class ITPTask


template <typename... ARGS>
class FunctionTask final : public ITPTask
{
public:
    explicit FunctionTask(std::function<void(ARGS...)> func, ARGS... args);
    ~FunctionTask() override = default;
    void Run() override;

private:
    std::function<void(ARGS...)> m_func;
    std::tuple<ARGS...> m_args;
}; //class FunctionTask

template <typename OUTPUT, typename... ARGS>
class FutureTask final : public ITPTask
{
public:
    explicit FutureTask(std::function<OUTPUT(ARGS...)> func, ARGS... args);
    ~FutureTask() override = default;
    void Run() override;
    OUTPUT Get();

private:
    std::binary_semaphore m_semaphore;
    std::function<OUTPUT(ARGS...)> m_func;
    std::tuple<ARGS...> m_args;
    OUTPUT m_retval;
}; //class FutureTask


//FunctionTask Definitions

template <typename ... ARGS>
FunctionTask<ARGS...>::FunctionTask(std::function<void(ARGS...)> func,
                                                            ARGS... args)
    : m_func(func), m_args(args...) {}

template <typename ... ARGS>
void FunctionTask<ARGS...>::Run()
{
    std::apply(m_func,m_args);
}

//Future Task Definitions

template <typename OUTPUT, typename ... ARGS>
FutureTask<OUTPUT, ARGS...>::FutureTask(std::function<OUTPUT(ARGS...)> func,
                                                                ARGS... args)
    : m_semaphore(0), m_func(func), m_args(args...) {}

template <typename OUTPUT, typename ... ARGS>
void FutureTask<OUTPUT, ARGS...>::Run()
{
    m_retval = std::apply(m_func,m_args);
    m_semaphore.release();
}

template <typename OUTPUT, typename ... ARGS>
OUTPUT FutureTask<OUTPUT, ARGS...>::Get()
{
    m_semaphore.acquire();
    return m_retval;
}

}

#endif //ILRD_R1645_ITPTASK_HPP
