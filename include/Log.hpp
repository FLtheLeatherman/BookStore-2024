#ifndef LOG_H
#define LOG_H

#include "MemoryRiver.hpp"
#include "Account.hpp"
#include "Book.hpp"

class Finance {
public:
    double income, expend;
    Finance();
    Finance(double income, double expend);
    bool operator <(const Finance &);
    bool operator ==(const Finance &);
    friend std::ostream& operator <<(std::ostream &, const Finance &);
};

class FinanceInfo {
public:
    String30 UserID;
    int len;
    std::array<char, 400> operation;
    Finance finance;
    FinanceInfo();
    FinanceInfo(String30, int, std::array<char, 400>, Finance);
    friend std::ostream& operator <<(std::ostream &, const FinanceInfo &);
};

class LogInfo {
public:
    String30 UserID;
    int len;
    std::array<char, 400> operation;
    LogInfo();
    LogInfo(String30, int, std::array<char, 400>);
};

class EmployeeLog {
public:
    int time;
    LogInfo log;
    EmployeeLog();
    EmployeeLog(int time, LogInfo log);
    bool operator <(const EmployeeLog &);
    bool operator ==(const EmployeeLog &);
    friend std::ostream& operator <<(std::ostream &, const EmployeeLog &);
};

class LogInfoStorage {
private:
    MemoryRiver<Finance, 1> financeStorage;
    MemoryRiver<FinanceInfo, 1> financeInfoStorage;
    MemoryRiver<LogInfo, 1> logStorage;
    MemoryRiver<String30, 2> employees;
    BlockList<String30, EmployeeLog> employeeStorage;
    const std::string headString1 = "UserID";
    const std::string headString2 = "Operation";
    const std::string headString3 = "Current income";
    const std::string headString4 = "Current expenditure";
    const std::string headString5 = "Time";
public:
    void initialize();
    void addFinance(double, double, String30, int, std::array<char, 400>);
    void addEmployee(String30);
    void addEmployeeLog(String30, int, std::array<char, 400>);
    void addLog(String30, int, std::array<char, 400>);
    bool showFinance(int Count);
    void showFinanceInfo();
    void showEmployeeLog();
    void showLog();
};

#endif