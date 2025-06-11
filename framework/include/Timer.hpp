/*******************************************************************************
* FileName: Timer                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: TBD                                                     *
 * Review Status: pre-APPROVED (25/03/2025)                                           *
 ******************************************************************************/

#ifndef ILRD_RD1645_TIMER_HPP
#define ILRD_RD1645_TIMER_HPP

#include <chrono> // std::chrono
#include <csignal> // sigevent

namespace ilrd
{

class Timer
{
public:
    explicit Timer(void (*timeIsOverFunc)(sigval sval), void* obj);
    ~Timer();
    void SetTime(std::chrono::time_point<std::chrono::system_clock> time_to_run);

private:
    sigevent m_sigevent;
    timer_t m_timer;
    itimerspec m_itimerspec;
}; // class Timer

} // namespace ilrd

#endif //ILRD_RD1645_TIMER_HPP
