
#ifndef ILRD_RD1645_DIRMONITOR_HPP
#define ILRD_RD1645_DIRMONITOR_HPP

#include <string>
#include <thread>

#include "Dispatcher.hpp"

namespace ilrd
{

class DirMonitor
{
public:
    explicit DirMonitor(const std::string& path_name = "./plugins");
    ~DirMonitor();
    DirMonitor(const DirMonitor& other) = delete;
    DirMonitor& operator=(const DirMonitor& other) = delete;
    DirMonitor(DirMonitor&& other) = delete;

    void RegisterForDelete(ACallback<const std::string&>* callback);
    void RegisterForModify(ACallback<const std::string&>* callback);
    void UnregisterForDelete(ACallback<const std::string&>* callback);
    void UnregisterForModify(ACallback<const std::string&>* callback);

    void Run();
private:
    void ThreadFunc();
    Dispatcher<const std::string&> m_deleteDispatcher;
    Dispatcher<const std::string&> m_modifyDispatcher;
    bool m_isRunning;
    std::jthread m_thread;
    std::string m_pathName;
    int m_infd;
    int m_inwatch;
}; // class DllMonitor

} // namespace ilrd

#endif //ILRD_RD1645_DIRMONITOR_HPP
