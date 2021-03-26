#include "FileLogger.hpp"
#include "LoggerImpl.hpp"

FileLogger::FileLogger(const std::string& fileName) :
    Logger(static_cast<std::unique_ptr<LoggerImpl>>(new LoggerImpl())),
    m_sFileName(fileName) {

}

void FileLogger::log(const std::string &str) {
    m_plogImpl->file_log(m_sFileName, str);
}
