/*******************************************************************************
* FileName: ReadResponse                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: TBD                                                     *
 * Review Status: pre-APPROVED (09/04/2025)                                           *
 ******************************************************************************/
//
// Created by ofir on 4/9/25.
//

#ifndef ILRD_RD1645_READRESPONSE_HPP
#define ILRD_RD1645_READRESPONSE_HPP
#include "IResponse.hpp"

namespace ilrd
{

class ReadResponse final: public IResponse
{
public:
 ReadResponse() = default;
 ~ReadResponse() override = default;
 void onSuccess(const std::shared_ptr<TaskResult>&) override;
 void onFailure(const std::shared_ptr<TaskResult>&) override;

}; // class ReadResponse

} // namespace ilrd

#endif //ILRD_RD1645_READRESPONSE_HPP
