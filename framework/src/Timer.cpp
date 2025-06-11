#include "Timer.hpp"
#include <stdexcept>

using namespace ilrd;

Timer::Timer(void(*timeIsOverFunc)(sigval sval), void* obj)
    : m_sigevent(), m_timer(), m_itimerspec()
{
    m_sigevent.sigev_notify = SIGEV_THREAD;
    m_sigevent.sigev_notify_function = timeIsOverFunc;
    m_sigevent.sigev_value.sival_ptr = obj;
    if(timer_create(CLOCK_REALTIME, &m_sigevent, &m_timer) == -1)
    {
        throw std::runtime_error("Error creating timer");
    }
}

Timer::~Timer()
{
    timer_delete(m_timer);
}

void Timer::SetTime(const std::chrono::time_point<std::chrono::system_clock> time_to_run)
{
    m_itimerspec.it_value.tv_sec = std::chrono::system_clock::to_time_t(time_to_run);
    m_itimerspec.it_value.tv_nsec = (time_to_run - std::chrono::system_clock::from_time_t(m_itimerspec.it_value.tv_sec)).count();

    if (timer_settime(m_timer, TIMER_ABSTIME, &m_itimerspec, nullptr) == -1)
    {
        timer_delete(m_timer);
        throw std::runtime_error("Error setting timer");
    }
}
