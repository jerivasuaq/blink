#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

// Log levels
enum LogLevel {
    LOG_DEBUG = 0,
    LOG_INFO = 1,
    LOG_WARN = 2,
    LOG_ERROR = 3,
    LOG_CRITICAL = 4
};

class Logger {
private:
    LogLevel currentLevel;
    bool useTimestamp;
    bool useColors;
    Stream* serialPort; // Pointer to any Stream (Serial, SoftwareSerial, etc.)
    
    // Color codes for ANSI terminals
    static const char* COLOR_DEBUG;
    static const char* COLOR_INFO;
    static const char* COLOR_WARN;
    static const char* COLOR_ERROR;
    static const char* COLOR_CRITICAL;
    static const char* COLOR_TAG;
    static const char* COLOR_RESET;
    
    // Get color for log level
    const char* getColorForLevel(LogLevel level);
    
    // Get emoji for log level
    const char* getEmojiForLevel(LogLevel level);
    
    // Get label for log level
    const char* getLabelForLevel(LogLevel level);
    
    // Print timestamp if enabled
    void printTimestamp();
    
public:
    // Constructor - defaults to Serial
    Logger(Stream& serialPort = Serial, LogLevel initialLevel = LOG_INFO, bool useTimestamp = true, bool useColors = true);
    
    // Set serial port (useful for SoftwareSerial or other Stream implementations)
    void setSerialPort(Stream& serialPort);
    
    // Set log level
    void setLogLevel(LogLevel level);
    
    // Get current log level
    LogLevel getLogLevel();
    
    // Enable/disable timestamp
    void setTimestamp(bool enable);
    
    // Enable/disable colors
    void setColors(bool enable);
    
    // Logging methods
    void debug(const char* tag, const char* message);
    void info(const char* tag, const char* message);
    void warn(const char* tag, const char* message);
    void error(const char* tag, const char* message);
    void critical(const char* tag, const char* message);
    
    // Formatted logging methods (variadic)
    void debugf(const char* tag, const char* format, ...);
    void infof(const char* tag, const char* format, ...);
    void warnf(const char* tag, const char* format, ...);
    void errorf(const char* tag, const char* format, ...);
    void criticalf(const char* tag, const char* format, ...);
    
private:
    // Internal log function
    void log(LogLevel level, const char* tag, const char* message);
};

// Global logger instance
extern Logger logger;

#endif // LOGGER_H
