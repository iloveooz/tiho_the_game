#ifndef TIHO_CONSOLELOGGER_HPP
#define TIHO_CONSOLELOGGER_HPP

#include "Logger.hpp"

class ConsoleLogger : public Logger {
public:
    ConsoleLogger();
    void log(const std::string& place, const std::string& event) override;
};

#endif //TIHO_CONSOLELOGGER_HPP
