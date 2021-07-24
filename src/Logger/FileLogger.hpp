#ifndef TIHO_FILELOGGER_HPP
#define TIHO_FILELOGGER_HPP

#include "Logger.hpp"

class FileLogger : public Logger {
public:
    explicit FileLogger(const std::string& fileName);
    ~FileLogger();
    void log(const std::string& place, const std::string& event) override;

private:
    std::string m_sFileName;
};

#endif //TIHO_FILELOGGER_HPP
