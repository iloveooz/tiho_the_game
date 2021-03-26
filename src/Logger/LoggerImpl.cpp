#include "LoggerImpl.hpp"

LoggerImpl::LoggerImpl() {}

void LoggerImpl::console_log(const std::string &str) {
    // Дата: Время: Класс: Метод: Событие
    std::cout << "Date: " << ", Time: " << ", Class: " << ", Method: " << ", Event: " << str << std::endl;
}

void LoggerImpl::file_log(const std::string &file, const std::string &str) {
    std::cout << "Date: " << ", Time: " << ", Class: " << ", Method: " << ", Event: " << str << std::endl;
}

void LoggerImpl::socket_log(const std::string &host, int port, const std::string &str) {
    std::cout << "Date: " << ", Time: " << ", Class: " << ", Method: " << ", Event: " << str << std::endl;
}
