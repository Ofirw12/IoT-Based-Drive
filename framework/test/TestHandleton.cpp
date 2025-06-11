
#include <dlfcn.h>
#include <iostream>

#include "Handleton.hpp"

class test
{
public:
    ~test()
    {
        std::cout << "test::~test()" << std::endl;
    }
};

void TestHandlenton()
{
    void* handle1 = dlopen("libhandleton_dll1.so", RTLD_LAZY);
    void* handle2 = dlopen("libhandleton_dll2.so", RTLD_LAZY);

    void* func1 = dlsym(handle1, "Do");
    void* func2 = dlsym(handle2, "DoHast");

    reinterpret_cast<void (*)()>(func1)();
    reinterpret_cast<void (*)()>(func2)();
    std::cout << ilrd::Handleton::GetInstance<int>() << std::endl;

    dlclose(handle1);
    dlclose(handle2);

    std::cout << ilrd::Handleton::GetInstance<test>() << std::endl;
}

int main()
{
    TestHandlenton();
    return 0;
}