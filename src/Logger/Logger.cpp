#include "Logger.hpp"
#include "LoggerImpl.hpp"

Logger::Logger(std::unique_ptr<LoggerImpl> pLogImpl) :
    m_plogImpl(std::move(pLogImpl)){}

// если не реализовать деструктор, валится ошибка undefined reference to `vtable for Logger'
Logger::~Logger() {}
