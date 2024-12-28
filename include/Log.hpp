#ifndef LOG_H
#define LOG_H

#include "MemoryRiver.hpp"

class LogInfo {
public:
    double income, expend;
    LogInfo();
    LogInfo(double income, double expend);
    bool operator <(const LogInfo &);
    bool operator ==(const LogInfo &);
    friend std::ostream& operator <<(std::ostream &, const LogInfo &);
};

class LogInfoStorage {
private:
    MemoryRiver<LogInfo, 1> storage;
public:
    void initialize();
    void addLog(double, double);
    bool showFinance(int Count);
};

#endif