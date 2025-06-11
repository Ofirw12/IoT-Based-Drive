/*******************************************************************************
* FileName: Handleton                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: Gil Fridman                                                       *
 * Review Status: APPROVED (17.3.25)                                           *
 ******************************************************************************/
#include "Handleton.hpp"

std::unordered_map<const std::type_info*, std::shared_ptr<void>,
                    ilrd::Handleton::HashFunction, ilrd::Handleton::EqualFunction>
                    ilrd::Handleton::m_instances;

std::mutex ilrd::Handleton::m_mutex;