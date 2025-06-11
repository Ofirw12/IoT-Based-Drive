
#include <ranges>

#include "IListener.hpp"

std::vector<std::pair<int, ilrd::FDMODE>> ilrd::LinuxListener::Listen(std::vector<std::pair<int, FDMODE>> vector)
{
    fd_set readset = {};
    fd_set writeset = {};
    FD_ZERO(&readset);
    FD_ZERO(&writeset);
    int maxfd = 0;

    for(auto [fst, snd] : vector)
    {
        if (snd == ilrd::WRITE)
        {
            FD_SET(fst, &writeset);
        }
        else
        {
            FD_SET(fst, &readset);
        }
        maxfd = std::max(maxfd, fst);
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