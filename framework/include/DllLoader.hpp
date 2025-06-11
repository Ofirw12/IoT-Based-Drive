/*******************************************************************************
* FileName: DllLoader                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: Liad Tiblum                                                       *
 * Review Status: APPROVED (24/3/25)                                           *
 ******************************************************************************/

#ifndef ILRD_RD1645_DLLLOADER_HPP
#define ILRD_RD1645_DLLLOADER_HPP

#include <unordered_map> // std::unordered_map
#include <string> // std::string

namespace ilrd
{

class DllLoader
{
public:
    DllLoader() = default;
    ~DllLoader();
    void Load(const std::string& dllPath);
    void Unload(const std::string& dllPath);
    void Reload(const std::string& dllPath);
private:
    typedef void* dlhandler;
    std::unordered_map<std::string, dlhandler> m_dlls;

}; // class DllLoader

} // namespace ilrd

#endif //ILRD_RD1645_DLLLOADER_HPP
