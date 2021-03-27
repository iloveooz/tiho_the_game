#ifndef TIHO_SOCKETLOGGER_HPP
#define TIHO_SOCKETLOGGER_HPP

#include "Logger.hpp"

class SocketLogger : public Logger {
public:
    SocketLogger(const std::string& remoteHost, long remotePort);
    void log(const std::string& cls, const std::string& meth, const std::string& event) override;

private:
    std::string m_sHost;
    long m_lPort;
};

#endif //TIHO_SOCKETLOGGER_HPP
