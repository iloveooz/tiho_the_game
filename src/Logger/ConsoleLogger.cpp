#include "ConsoleLogger.hpp"
#include "LoggerImpl.hpp"

ConsoleLogger::ConsoleLogger() :
    Logger(static_cast<std::unique_ptr<LoggerImpl>>(new LoggerImpl())) {

}

void ConsoleLogger::log(const std::string& cls, const std::string& meth, const std::string &event) {
    m_plogImpl->console_log(cls, meth, event);
}
