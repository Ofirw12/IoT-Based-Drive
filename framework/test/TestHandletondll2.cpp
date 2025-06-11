
#include <iostream>

#include "Handleton.hpp"

extern "C" void DoHast()
{
    std::cout << ilrd::Handleton::GetInstance<int>() << std::endl;
}