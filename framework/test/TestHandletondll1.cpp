
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

extern "C" void Do()
{
    std::cout << ilrd::Handleton::GetInstance<int>() << std::endl;
    ilrd::Handleton::GetInstance<test>();
}