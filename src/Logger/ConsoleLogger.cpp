#include "ConsoleLogger.hpp"
#include "LoggerImpl.hpp"

ConsoleLogger::ConsoleLogger() :
    Logger(static_cast<std::unique_ptr<LoggerImpl>>(new LoggerImpl())) {

}

void ConsoleLogger::log(const std::string &str) {
    m_plogImpl->console_log(str);
}
