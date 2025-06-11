
#include <iostream>
#include <thread>

#include "Singleton.hpp"

class Company
{
public:
    void WorkDay()
    {
        std::cout << "Work day" << std::endl;
        std::cout << "Danny the driver drives to Dimona" << std::endl;
        std::cout << "Mani the manager is managing" << std::endl;
        std::cout << "Pen the painter is painting pens" << std::endl;
    }
    void Fire()
    {
        std::cout << "Fire" << std::endl;
        std::cout << "Mani the manager is fired" << std::endl;
    }

private:
    friend class ilrd::Singleton<Company>;
    Company() = default;
    Company(const Company&) = default;
    Company& operator=(const Company&) = default;
};

void ThreadFunc1()
{
    size_t i = 200;
    while (i-- != 0)
    {
        try
        {
            std::string* const str =  ilrd::Singleton<std::string>::GetInstance();
            str->append("a");
        }
        catch (const std::runtime_error& e)
        {
            std::cout << e.what() << std::endl;
            break;
        }
    }
}

void ThreadFunc2()
{
    size_t i = 0;
    while (i < 20)
    {
        std::cout << *ilrd::Singleton<std::string>::GetInstance() << std::endl;
        ++i;
    }
}

void TestSingleton()
{
    std::string* const instance = ilrd::Singleton<std::string>::GetInstance();
    ilrd::Singleton<std::string>::GetInstance()->append("TestSingleton");
    std::cout << ilrd::Singleton<std::string>::GetInstance()->c_str() << std::endl;
    *instance = "Blabla";
    std::cout << *ilrd::Singleton<std::string>::GetInstance() << std::endl;

    std::jthread one(ThreadFunc1);
    std::jthread two(ThreadFunc2);
    sleep(5);
    try
    {
        ilrd::Singleton<std::string>::GetInstance()->append("Destructed test");
        std::cout << ilrd::Singleton<std::string>::GetInstance()->c_str() << std::endl;
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
    }

    Company* com = ilrd::Singleton<Company>::GetInstance();
    com->WorkDay();
    com->Fire();
}

int main()
{
    TestSingleton();
    return 0;
}