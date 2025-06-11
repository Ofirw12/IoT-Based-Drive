/*******************************************************************************
* FileName: IListener                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: Mor Weisberg                                                      *
 * Review Status: APPROVED (23/03/25)                                          *
 ******************************************************************************/

#ifndef ILRD_RD1645_ILISTENER_HPP
#define ILRD_RD1645_ILISTENER_HPP
#include <vector>

namespace ilrd
{

enum FDMODE
{
 READ = 0,
 WRITE = 1,
};

class IListener
{
public:
 virtual ~IListener() = default;
 virtual std::vector<std::pair<int, FDMODE>> Listen(std::vector<std::pair<int, FDMODE>> vector) = 0;
}; // class IListener

class LinuxListener final : public IListener
{
public:
 std::vector<std::pair<int, FDMODE>> Listen(std::vector<std::pair<int, FDMODE>> vector) override;
};

} // namespace ilrd

#endif //ILRD_RD1645_ILISTENER_HPP
