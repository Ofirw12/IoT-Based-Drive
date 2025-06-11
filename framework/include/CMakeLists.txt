cmake_minimum_required(VERSION 3.20)

target_sources(handleton_shared PRIVATE Handleton.hpp)

target_sources(logger_shared PRIVATE Logger.hpp WaitableQueue.hpp)

target_sources(reactor_static PRIVATE Reactor.hpp IListener.hpp)
target_sources(reactor_shared PRIVATE Reactor.hpp IListener.hpp)

target_sources(framework_static PRIVATE Framework.hpp FW_TPTask.hpp)
target_sources(framework_shared PRIVATE Framework.hpp FW_TPTask.hpp)