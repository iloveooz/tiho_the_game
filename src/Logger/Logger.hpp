#ifndef TIHO_LOGGER_HPP
#define TIHO_LOGGER_HPP

#include <string>
#include <memory>

class LoggerImpl;

class Logger {
public:
    explicit Logger(std::unique_ptr<LoggerImpl> pLogImpl);
    virtual ~Logger();

    virtual void log(const std::string& str) = 0;

protected:
    std::unique_ptr<LoggerImpl> m_plogImpl;
};

#endif //TIHO_LOGGER_HPP
