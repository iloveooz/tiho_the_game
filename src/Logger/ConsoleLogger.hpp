#ifndef TIHO_CONSOLELOGGER_HPP
#define TIHO_CONSOLELOGGER_HPP

#include "Logger.hpp"

class ConsoleLogger : public Logger {
public:
    ConsoleLogger();
    void log(const std::string& cls, const std::string& meth, const std::string& event) override;
};

#endif //TIHO_CONSOLELOGGER_HPP
