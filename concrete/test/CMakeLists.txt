cmake_minimum_required(VERSION 3.20)

add_executable(amessages TestAMessages.cpp)
target_link_libraries(amessages messages_static uid_static)

add_executable(minion TestMinion.cpp)
target_link_libraries(minion minion_static framework_static)

add_executable(filezeroer FileCreator.cpp)