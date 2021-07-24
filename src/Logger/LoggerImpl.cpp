#include "LoggerImpl.hpp"

LoggerImpl::LoggerImpl() {
    try {
        out.open("output.txt", std::ofstream::out);
    }
    catch (...) {}

    if(!out) {
        throw std::runtime_error("Could not open file : for writing");
    }
}

LoggerImpl::~LoggerImpl() noexcept {
    try {
        if (out.is_open())
            out.close();
    }
    catch (...) {}
}

void LoggerImpl::console_log(const std::string& place, const std::string &event) {
    // Дата: Время: Класс: Метод: Событие
    std::string time(21, ' ');
    getTime(time);

    std::cout << time << place << ", event: " << event << std::endl;
}

void LoggerImpl::file_log(const std::string& place, const std::string &fileName, const std::string &event) {

    if (!out) {
        std::cerr << "\nError opening file!" << std::endl;
    }

    // Дата: Время: Класс: Метод: Событие
    std::string time(21, ' ');
    getTime(time);

    out << time << ", " << place.c_str() << ", event: " << event.c_str() << std::endl;
}

void LoggerImpl::socket_log(const std::string& place, const std::string &host, long port, const std::string &event) {
    // Дата: Время: Класс: Метод: Событие
    std::string time;
    getTime(time);

    std::cout << time << ", " << place << ", event: " << event << std::endl;
}

void LoggerImpl::getTime(std::string &time) {
    std::time_t timeNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); // get time now

    std::strftime(&time[0], time.size(), "%d-%m-%Y, %H:%M:%S:", std::localtime(&timeNow));
}
