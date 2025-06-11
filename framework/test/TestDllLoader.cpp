
#include <Factory.hpp>
#include <iostream>

#include "Handleton.hpp"
#include "ICommand.hpp"
#include "IListener.hpp"

class NewRead final : public ilrd::ICommand
{
    std::optional<std::pair<std::function<bool()>, std::chrono::milliseconds>> Run(std::shared_ptr<ilrd::ITaskArgs> args) override
    {
        std::pair<std::function<bool()>, std::chrono::milliseconds> result;
        std::cout << "NewTaskDll" << std::endl;
        result.first = []{return true;};
        result.second = std::chrono::milliseconds(1000);
        return result;
    }
};

__attribute__((constructor))
void Create()
{
    std::cout << "NewRead" << std::endl;
    ilrd::Handleton::GetInstance<ilrd::Factory<int, ilrd::ICommand>>()->Register(ilrd::READ, []{return new NewRead;});
}

__attribute__((destructor))
void Destroy()
{
    std::cout << "NewRead Destroyed" << std::endl;
}