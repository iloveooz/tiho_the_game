#include "FileLogger.hpp"
#include "LoggerImpl.hpp"

FileLogger::FileLogger(const std::string& fileName) :
        Logger(static_cast<std::unique_ptr<LoggerImpl>>(new LoggerImpl())),
        m_sFileName(fileName) {

}

FileLogger::~FileLogger() {
}

void FileLogger::log(const std::string& cls, const std::string& meth, const std::string &event) {
    m_plogImpl->file_log(cls, meth, m_sFileName, event);
}


