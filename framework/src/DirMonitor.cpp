
#include <cstring>
#include <sys/inotify.h>

#include "DirMonitor.hpp"

static int GetInFd()
{
    const int infd = inotify_init();
    if (infd == -1)
    {
        throw std::runtime_error("Failed to initialize inotify");
    }
    return infd;
}

static int GetInWatch(int fd, const std::string& path_name)
{
    const int notifier = inotify_add_watch(fd, path_name.c_str(),
                                        IN_DELETE | IN_CLOSE_WRITE);
    if (notifier == -1)
    {
        close(fd);
        throw std::runtime_error("Failed to add watch");
    }

    return notifier;
}

ilrd::DirMonitor::DirMonitor(const std::string& path_name)
    : m_isRunning(false) , m_pathName(path_name),
        m_infd(GetInFd()), m_inwatch(GetInWatch(m_infd, path_name)) {}

ilrd::DirMonitor::~DirMonitor()
{
    m_isRunning = false;
    inotify_rm_watch(m_infd, m_inwatch);
    close(m_infd);
}

void ilrd::DirMonitor::RegisterForDelete(ACallback<const std::string&>* callback)
{
    m_deleteDispatcher.Register(callback);
}

void ilrd::DirMonitor::RegisterForModify(ACallback<const std::string&>* callback)
{
    m_modifyDispatcher.Register(callback);
}

void ilrd::DirMonitor::UnregisterForDelete(
    ACallback<const std::string&>* callback)
{
    m_deleteDispatcher.Unregister(callback);
}

void ilrd::DirMonitor::UnregisterForModify(
    ACallback<const std::string&>* callback)
{
    m_modifyDispatcher.Unregister(callback);
}

void ilrd::DirMonitor::Run()
{
    m_thread = std::jthread([this] {ThreadFunc();});
}

void ilrd::DirMonitor::ThreadFunc()
{
    m_isRunning = true;
    while(m_isRunning)
    {
        constexpr int bufsize =  (sizeof(inotify_event) + 16) * 1024;
        char buffer[bufsize] = {};

        const int bytes = read(m_infd, &buffer, bufsize);
        int i = 0;
        while (i < bytes)
        {
            const auto* ie = reinterpret_cast<inotify_event*>(&buffer[i]);

            std::string full_path = m_pathName + "/" + ie->name;
            if (ie->mask & IN_CLOSE_WRITE)
            {
                m_modifyDispatcher.Notify(full_path);
            }
            else if (ie->mask & IN_DELETE)
            {
                m_deleteDispatcher.Notify(full_path);
            }
            i += sizeof(inotify_event) + ie->len;
        }
    }
}
