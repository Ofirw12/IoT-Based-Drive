/*******************************************************************************
* FileName: Response                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: TBD                                                     *
 * Review Status: pre-APPROVED (06/04/2025)                                           *
 ******************************************************************************/
//
// Created by ofir on 4/6/25.
//

#ifndef ILRD_RD1645_WRITERESPONSE_HPP
#define ILRD_RD1645_WRITERESPONSE_HPP

#include "IResponse.hpp"

namespace ilrd
{

class WriteResponse final : public IResponse
{
public:
    WriteResponse() = default;
	~WriteResponse() override = default;
    void onSuccess(const std::shared_ptr<TaskResult>&) override;
    void onFailure(const std::shared_ptr<TaskResult>&) override;

}; // class Response

} // namespace ilrd

#endif //ILRD_RD1645_RESPONSE_HPP
