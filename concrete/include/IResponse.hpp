/*******************************************************************************
* FileName: IResponse                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: TBD                                                     *
 * Review Status: pre-APPROVED (06/04/2025)                                           *
 ******************************************************************************/
//
// Created by ofir on 4/6/25.
//

#ifndef ILRD_RD1645_IRESPONSE_HPP
#define ILRD_RD1645_IRESPONSE_HPP

#include "Ticket.hpp"

namespace ilrd
{

class IResponse
{
public:
	virtual ~IResponse() = default;
	virtual void onSuccess(const std::shared_ptr<TaskResult>&) = 0;
	virtual void onFailure(const std::shared_ptr<TaskResult>&) = 0;
}; // class IResponse

} // namespace ilrd

#endif //ILRD_RD1645_IRESPONSE_HPP
