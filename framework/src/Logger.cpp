/*******************************************************************************
* FileName: Logger                                                             *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: Mor Weisberg                                                      *
 * Review Status: APPROVED (19/3/25)                                           *
 ******************************************************************************/
#include <iosfwd>
#include <iomanip>
#include "Logger.hpp"

ilrd::Logger::Logger() :m_severities("Debug", "Warning", "Error"),
                                    m_isRunning(true)
{
    m_thread = std::jthread([this]{ThreadFunc();});
}

void ilrd::Logger::ThreadFunc()
{
    std::ofstream m_file("Log.txt", std::ios::out | std::ios::app);
    while (m_isRunning || !m_logQueue.IsEmpty())
    {
        std::ostringstream oss;
        std::tuple<std::time_t, SEVERITY, std::string> data;
        m_logQueue.Pop(data);
        oss << std::put_time(std::localtime(&std::get<std::time_t>(data)), "%d-%m-%Y %T ");
        oss << "Severity: " << m_severities[std::get<SEVERITY>(data)];
        oss << " , " << std::get<std::string>(data);
        const std::string str = oss.str();
        m_file << str << std::endl;
    }
}

void ilrd::Logger::Log(const std::string& str, SEVERITY severity)
{
    std::time_t now =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    m_logQueue.Push(std::make_tuple(now, severity, str));
}

ilrd::Logger::~Logger()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    const std::string str = "Logger Is Shutting Down.";
    m_isRunning = false;
    m_logQueue.Push(std::make_tuple(now, WARNING, str));
}