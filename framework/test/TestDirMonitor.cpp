#include <iostream>

#include "DirMonitor.hpp"
#include "DllLoader.hpp"

class Printer
{
public:
    void PrintAdd(const std::string& str)
    {
        std::cout << "Printer::PrintAdd: " << str << std::endl;
    }

    void PrintRemove(const std::string& str)
    {
        std::cout << "Printer::PrintRemove: " << str << std::endl;
    }

    void PrintModify(const std::string& str)
    {
        std::cout << "Printer::PrintModify: " << str << std::endl;
    }
};

void TestDirMonitor()
{
    ilrd::DirMonitor monitor;
    Printer printer;
    ilrd::DllLoader loader;
    ilrd::Callback printadd(printer, &Printer::PrintAdd);
    ilrd::Callback printremove(printer, &Printer::PrintRemove);
    ilrd::Callback loadcallback(loader, &ilrd::DllLoader::Load);
    ilrd::Callback unloadcallback(loader, &ilrd::DllLoader::Unload);
    ilrd::Callback reloadcallback(loader, &ilrd::DllLoader::Reload);
    ilrd::Callback modify(printer, &Printer::PrintModify);
    monitor.RegisterForModify(&printadd);
    monitor.RegisterForModify(&loadcallback);
    monitor.RegisterForDelete(&unloadcallback);
    monitor.RegisterForDelete(&printremove);

    monitor.Run();
    // while(true);
    sleep(1);
}

int main()
{
    TestDirMonitor();
    return 0;
}