#ifndef ILRD_R1645_LOGGER_HPP
#define ILRD_R1645_LOGGER_HPP

#include <string>
#include <fstream>
#include <thread>

#include "WaitableQueue.hpp"
#include "Handleton.hpp"

namespace ilrd
{
class Logger
{
public:
    enum SEVERITY
    {
        DEBUG = 0,
        WARNING = 1,
        ERROR = 2,
        NUM_OF_SEVERITIES
    };

    void Log(const std::string& str, SEVERITY severity);
    ~Logger();
private:
    friend class Handleton;
    void ThreadFunc();
    Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    WaitableQueue<std::tuple<std::time_t, SEVERITY, std::string>> m_logQueue;
    std::string m_severities[NUM_OF_SEVERITIES];
    bool m_isRunning;
    std::jthread m_thread;

}; // class Logger

} // namespace ilrd
#endif //ILRD_R1645_LOGGER_HPP