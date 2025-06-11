#include "Logger.hpp"
#include "Handleton.hpp"

void TestLogger()
{
    for (size_t i = 0; i < 10 ; ++i)
    {
        ilrd::Handleton::GetInstance<ilrd::Logger>()->Log("Zack Is Hazak", ilrd::Logger::ERROR);
    }
}

int main()
{
    TestLogger();
    return 0;
}