#ifndef TIHO_CONSOLELOGGER_HPP
#define TIHO_CONSOLELOGGER_HPP

#include "Logger.hpp"

class ConsoleLogger : public Logger {
public:
    ConsoleLogger();
    void log(const std::string& str) override;
};

#endif //TIHO_CONSOLELOGGER_HPP
