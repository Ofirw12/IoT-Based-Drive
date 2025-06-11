
#include <dlfcn.h> // dlopen, dlclose
#include <stdexcept> // std::runtime_error
#include "DllLoader.hpp"

ilrd::DllLoader::~DllLoader()
{
    for (auto it = m_dlls.begin(); it != m_dlls.end(); ++it)
    {
        if (dlclose(it->second))
        {
            throw std::runtime_error("DllLoader::~DllLoader(): Failed to close library");
        }
    }
}

void ilrd::DllLoader::Load(const std::string& dllPath)
{
        const dlhandler dll = dlopen(dllPath.c_str(), RTLD_LAZY);
        if (!dll)
        {
            throw std::runtime_error(dlerror());
        }
        m_dlls[dllPath] = dll;
}

void ilrd::DllLoader::Unload(const std::string& dllPath)
{
    if(m_dlls.contains(dllPath))
    {
        if (dlclose(m_dlls[dllPath]))
        {
            throw std::runtime_error("DllLoader::Unload(): Failed to close library");
        }
        m_dlls.erase(dllPath);
    }
}

void ilrd::DllLoader::Reload(const std::string& dllPath)
{
    Unload(dllPath);
    Load(dllPath);
}
