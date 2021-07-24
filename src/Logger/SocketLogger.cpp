#include "SocketLogger.hpp"
#include "LoggerImpl.hpp"

SocketLogger::SocketLogger(const std::string &remoteHost, long remotePort) :
    Logger(static_cast<std::unique_ptr<LoggerImpl>>(new LoggerImpl())),
    m_sHost(remoteHost),
    m_lPort(remotePort) {

}

void SocketLogger::log(const std::string& place, const std::string &event) {
    m_plogImpl->socket_log(place, m_sHost, m_lPort, event);
}
