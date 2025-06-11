
#include <ranges>

#include "IListener.hpp"

std::vector<std::pair<int, ilrd::FDMODE>> ilrd::LinuxListener::Listen(std::vector<std::pair<int, FDMODE>> vector)
{
    fd_set readset = {};
    fd_set writeset = {};
    FD_ZERO(&readset);
    FD_ZERO(&writeset);
    int maxfd = 0;

    for(auto item : vector)
    {
        if (item.second == ilrd::WRITE)
        {
            FD_SET(item.first, &writeset);
        }
        else
        {
            FD_SET(item.first, &readset);
        }
        maxfd = std::max(maxfd, item.first);
    }

    select(maxfd + 1, &readset, &writeset, nullptr, nullptr);
    std::vector<std::pair<int, ilrd::FDMODE>> res;
    res.reserve(vector.size());
    for(const auto item : vector)
    {
        if (FD_ISSET(item.first, &readset))
        {
            res.push_back(item);
        }
    }

    return res;
}