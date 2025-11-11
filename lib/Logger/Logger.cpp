#include "Logger.h"
#include <stdarg.h>

// ANSI color codes
const char* Logger::COLOR_DEBUG = "\033[36m";      // Cyan
const char* Logger::COLOR_INFO = "\033[32m";       // Green
const char* Logger::COLOR_WARN = "\033[33m";       // Yellow
const char* Logger::COLOR_ERROR = "\033[31m";      // Red
const char* Logger::COLOR_CRITICAL = "\033[35m";   // Magenta
const char* Logger::COLOR_RESET = "\033[0m";       // Reset

// Global logger instance
Logger logger(Serial, LOG_INFO);

Logger::Logger(Stream& serialPort, LogLevel initialLevel, bool useTimestamp, bool useColors)
    : serialPort(&serialPort), currentLevel(initialLevel), useTimestamp(useTimestamp), useColors(useColors) {
}

void Logger::setLogLevel(LogLevel level) {
    currentLevel = level;
}

LogLevel Logger::getLogLevel() {
    return currentLevel;
}

void Logger::setSerialPort(Stream& serialPort) {
    this->serialPort = &serialPort;
}

void Logger::setTimestamp(bool enable) {
    useTimestamp = enable;
}

void Logger::setColors(bool enable) {
    useColors = enable;
}

const char* Logger::getColorForLevel(LogLevel level) {
    if (!useColors) return "";
    
    switch (level) {
        case LOG_DEBUG:
            return COLOR_DEBUG;
        case LOG_INFO:
            return COLOR_INFO;
        case LOG_WARN:
            return COLOR_WARN;
        case LOG_ERROR:
            return COLOR_ERROR;
        case LOG_CRITICAL:
            return COLOR_CRITICAL;
        default:
            return COLOR_RESET;
    }
}

const char* Logger::getLabelForLevel(LogLevel level) {
    switch (level) {
        case LOG_DEBUG:
            return "[DEBUG]";
        case LOG_INFO:
            return "[INFO]";
        case LOG_WARN:
            return "[WARN]";
        case LOG_ERROR:
            return "[ERROR]";
        case LOG_CRITICAL:
            return "[CRITICAL]";
        default:
            return "[UNKNOWN]";
    }
}

void Logger::printTimestamp() {
    if (useTimestamp) {
        unsigned long ms = millis();
        unsigned long seconds = ms / 1000;
        unsigned long milliseconds = ms % 1000;
        
        serialPort->print("[");
        if (seconds < 10) serialPort->print("0");
        serialPort->print(seconds);
        serialPort->print(".");
        if (milliseconds < 100) serialPort->print("0");
        if (milliseconds < 10) serialPort->print("0");
        serialPort->print(milliseconds);
        serialPort->print("] ");
    }
}

void Logger::log(LogLevel level, const char* tag, const char* message) {
    if (level < currentLevel) {
        return; // Skip this log if below current level
    }
    
    serialPort->print(getColorForLevel(level));
    printTimestamp();
    serialPort->print(getLabelForLevel(level));
    serialPort->print(" ");
    serialPort->print(tag);
    serialPort->print(": ");
    serialPort->print(message);
    serialPort->println(useColors ? COLOR_RESET : "");
}

void Logger::debug(const char* tag, const char* message) {
    log(LOG_DEBUG, tag, message);
}

void Logger::info(const char* tag, const char* message) {
    log(LOG_INFO, tag, message);
}

void Logger::warn(const char* tag, const char* message) {
    log(LOG_WARN, tag, message);
}

void Logger::error(const char* tag, const char* message) {
    log(LOG_ERROR, tag, message);
}

void Logger::critical(const char* tag, const char* message) {
    log(LOG_CRITICAL, tag, message);
}

void Logger::debugf(const char* tag, const char* format, ...) {
    if (LOG_DEBUG < currentLevel) return;
    
    va_list args;
    va_start(args, format);
    
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    
    va_end(args);
    
    log(LOG_DEBUG, tag, buffer);
}

void Logger::infof(const char* tag, const char* format, ...) {
    if (LOG_INFO < currentLevel) return;
    
    va_list args;
    va_start(args, format);
    
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    
    va_end(args);
    
    log(LOG_INFO, tag, buffer);
}

void Logger::warnf(const char* tag, const char* format, ...) {
    if (LOG_WARN < currentLevel) return;
    
    va_list args;
    va_start(args, format);
    
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    
    va_end(args);
    
    log(LOG_WARN, tag, buffer);
}

void Logger::errorf(const char* tag, const char* format, ...) {
    if (LOG_ERROR < currentLevel) return;
    
    va_list args;
    va_start(args, format);
    
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    
    va_end(args);
    
    log(LOG_ERROR, tag, buffer);
}

void Logger::criticalf(const char* tag, const char* format, ...) {
    if (LOG_CRITICAL < currentLevel) return;
    
    va_list args;
    va_start(args, format);
    
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    
    va_end(args);
    
    log(LOG_CRITICAL, tag, buffer);
}
