//
// Created by ofir on 3/17/25.
//

#include <iostream>

#include "Handleton.hpp"

extern "C" void DoHast()
{
    std::cout << ilrd::Handleton::GetInstance<int>() << std::endl;
}