/*******************************************************************************
* FileName: IFileManager                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: TBD                                                     *
 * Review Status: pre-APPROVED (20/04/2025)                                           *
 ******************************************************************************/
//
// Created by ofir on 4/20/25.
//

#ifndef ILRD_RD1645_IFILEMANAGER_HPP
#define ILRD_RD1645_IFILEMANAGER_HPP

#include <memory>
namespace ilrd
{

class IFileManager
{
public:
	virtual ~IFileManager() = default;
	virtual bool Read(size_t offset, size_t len, std::shared_ptr<char[]> to) = 0;
	virtual bool Write(size_t offset, size_t len, std::shared_ptr<char[]> from) = 0;
}; // class IFileManager

} // namespace ilrd

#endif //ILRD_RD1645_IFILEMANAGER_HPP
