#ifndef TIHO_FILELOGGER_HPP
#define TIHO_FILELOGGER_HPP

#include "Logger.hpp"

class FileLogger : public Logger {
public:
    explicit FileLogger(const std::string& fileName);
    void log(const std::string& str) override;

private:
    std::string m_sFileName;
};

#endif //TIHO_FILELOGGER_HPP
