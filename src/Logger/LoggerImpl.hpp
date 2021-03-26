#ifndef TIHO_LOGGERIMPL_HPP
#define TIHO_LOGGERIMPL_HPP

#include <string>
#include <iostream>

class LoggerImpl {
public:
    LoggerImpl();
    virtual ~LoggerImpl( ) {}
    virtual void console_log(const std::string& str);
    virtual void file_log(const std::string& file, const std::string & str);
    virtual void socket_log(const std::string& host, int port, const std::string& str);
};

#endif //TIHO_LOGGERIMPL_HPP
