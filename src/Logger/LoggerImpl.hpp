#ifndef TIHO_LOGGERIMPL_HPP
#define TIHO_LOGGERIMPL_HPP

#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>

class LoggerImpl {
public:
    LoggerImpl();
    virtual ~LoggerImpl();
    virtual void console_log(const std::string& place, const std::string& event);
    virtual void    file_log(const std::string& place, const std::string& fileName, const std::string & event);
    virtual void  socket_log(const std::string& place, const std::string& host, long port, const std::string& event);

private:
    static void getTime(std::string& time);
    std::ofstream out;
};

#endif //TIHO_LOGGERIMPL_HPP
