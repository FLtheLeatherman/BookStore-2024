#include <iostream>
#include "Log.hpp"

Finance::Finance() {
    income = expend = 0;
}
Finance::Finance(double income, double expend) {
    this->income = income;
    this->expend = expend;
}
bool Finance::operator <(const Finance& RHS) {
    return true;
}
bool Finance::operator ==(const Finance& RHS) {
    return true;
}
std::ostream& operator <<(std::ostream &out, const Finance& finance) {
    out << finance.income << ' ' << finance.expend;
    return out;
}

FinanceInfo::FinanceInfo() {
    UserID = String30();
    len = 0;
    finance = Finance();
}
FinanceInfo::FinanceInfo(String30 UserID, int len, std::array<char, 400> str, Finance finance) {
    this->UserID = UserID;
    this->len = len;
    this->operation = str;
    this->finance = finance;
}
std::ostream& operator <<(std::ostream &out, const FinanceInfo& financeInfo) {
    out << financeInfo.UserID << '\t';
    for (size_t i = 0; i < financeInfo.len; ++i) {
        out << financeInfo.operation[i];
    }
    out << '\t';
    out << financeInfo.finance.income << '\t' << financeInfo.finance.expend << '\n';
    return out;
}

LogInfo::LogInfo() {
    UserID = String30();
    len = 0;
}
LogInfo::LogInfo(String30 UserID, int len, std::array<char, 400> str) {
    this->UserID = UserID;
    this->len = len;
    this->operation = str;
}

EmployeeLog::EmployeeLog() {
    time = -1;
    log = LogInfo();
}
EmployeeLog::EmployeeLog(int time, LogInfo log) {
    this->time = time;
    this->log.UserID = log.UserID;
    this->log.len = log.len;
    this->log.operation = log.operation;
}
bool EmployeeLog::operator <(const EmployeeLog &RHS) {
    return this->time < RHS.time;
}
bool EmployeeLog::operator ==(const EmployeeLog &RHS) {
    return this->time == RHS.time;
}
std::ostream& operator <<(std::ostream &os, const EmployeeLog &RHS) {
    os << RHS.time;
    return os;
}

void LogInfoStorage::initialize() {
    financeStorage.initialize("Finance");
    financeInfoStorage.initialize("FinanceInfo");
    logStorage.initialize("Log");
    employeeStorage.initialize("EmployeeInfo");
    employees.initialize("Employee");
    employees.write_info(1, 1);
    std::string root = "root";
    String30 tmp = root;
    employees.write(tmp, 1);
}
void LogInfoStorage::addFinance(double income, double expend, String30 UserID, int len, std::array<char, 400> operation) {
    int nowLen;
    Finance lst;
    financeStorage.get_info(nowLen, 1);
    if (nowLen > 0) financeStorage.read(lst, nowLen);
    nowLen++;
    lst.income += income, lst.expend += expend;
    FinanceInfo tmp(UserID, len, operation, lst);
    financeStorage.write_info(nowLen, 1);
    financeStorage.write(lst, nowLen);
    financeInfoStorage.write_info(nowLen, 1);
    financeInfoStorage.write(tmp, nowLen);
}
void LogInfoStorage::addEmployee(String30 UserID) {
    int len = 0;
    employees.get_info(len, 1);
    len++;
    employees.write(UserID, len);
    employees.write_info(len, 1);
}
void LogInfoStorage::addEmployeeLog(String30 UserID, int len, std::array<char, 400> operation) {
    LogInfo tmp(UserID, len, operation);
    int time;
    employees.get_info(time, 2);
    time++;
    EmployeeLog ep(time, tmp);
    employeeStorage.insert(UserID, ep);
    employees.write_info(time, 2);
}
void LogInfoStorage::addLog(String30 UserID, int len, std::array<char, 400> operation) {
    int nowLen;
    logStorage.get_info(nowLen, 1);
    nowLen++;
    LogInfo tmp(UserID, len, operation);
    logStorage.write_info(nowLen, 1);
    logStorage.write(tmp, nowLen);
}
bool LogInfoStorage::showFinance(int Count) {
    int len;
    financeStorage.get_info(len, 1);
    if (Count > len) {
        return false;
    }
    if (!Count) {
        std::cout << '\n';
    } else {
        if (Count == len || Count == -1) {
            Finance tmp;
            financeStorage.read(tmp, len);
            std::cout << "+ " << tmp.income << " - " << tmp.expend << '\n';
        } else {
            Finance tmp1, tmp2;
            financeStorage.read(tmp1, len);
            financeStorage.read(tmp2, len - Count);
            tmp1.income -= tmp2.income;
            tmp1.expend -= tmp2.expend;
            std::cout << "+ " << tmp1.income << " - " << tmp1.expend << '\n';
        }
    }
    return true;
}
void LogInfoStorage::showFinanceInfo() {
    std::cout << "The Finance Report of Bookstore!\n";
    int len;
    financeInfoStorage.get_info(len, 1);
    size_t maxLen1 = headString1.size(), maxLen2 = headString2.size();
    size_t maxLen3 = headString3.size(), maxLen4 = headString4.size();
    for (size_t i = 0; i < len; ++i) {
        FinanceInfo tmp;
        financeInfoStorage.read(tmp, i + 1);
        maxLen1 = std::max(maxLen1, tmp.UserID.getLen());
        maxLen2 = std::max(maxLen2, (size_t)tmp.len);
        maxLen3 = std::max(maxLen3, std::to_string(tmp.finance.income).size() - 4);
        maxLen4 = std::max(maxLen4, std::to_string(tmp.finance.expend).size() - 4);
    }
    std::cout << headString1;
    for (size_t i = headString1.size(); i <= maxLen1; ++i) {
        std::cout << ' ';
    }
    std::cout << ' ' << headString2;
    for (size_t i = headString2.size(); i <= maxLen2; ++i) {
        std::cout << ' ';
    }
    std::cout << ' ' << headString3 << ' ' << ' ' << headString4 << '\n';
    for (size_t i = 0; i < len; ++i) {
        FinanceInfo tmp;
        financeInfoStorage.read(tmp, i + 1);
        std::cout << tmp.UserID;
        for (size_t i = tmp.UserID.getLen(); i <= maxLen1; ++i) {
            std::cout << ' ';
        }
        std::cout << ' ';
        for (size_t i = 0; i <= maxLen2; ++i) {
            if (i < tmp.len) {
                std::cout << tmp.operation[i];
            } else {
                std::cout << ' ';
            }
        }
        std::cout << ' ';
        std::string income = std::to_string(tmp.finance.income);
        std::string expend = std::to_string(tmp.finance.expend);
        for (size_t i = 0; i <= maxLen3; ++i) {
            if (i < income.size() - 4) {
                std::cout << income[i];
            } else {
                std::cout << ' ';
            }
        }
        std::cout << ' ';
        for (size_t i = 0; i < maxLen4; ++i) {
            if (i < expend.size() - 4) {
                std::cout << expend[i];
            } else {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
}
void LogInfoStorage::showEmployeeLog() {
    std::cout << "The Employee Report of Bookstore!\n";
    int len;
    employees.get_info(len, 1);
    for (size_t i = 0; i < len; ++i) {
        String30 UserID;
        employees.read(UserID, i + 1);
        std::vector<EmployeeLog> res = employeeStorage.query(UserID);
        std::cout << "The report of " << UserID << ":\n";
        size_t maxLen2 = headString2.size(), maxLen5 = headString5.size();
        for (size_t j = 0; j < res.size(); ++j) {
            maxLen2 = std::max(maxLen2, (size_t)res[j].log.len);
            maxLen5 = std::max(maxLen5, std::to_string(res[i].time).size());
        }
        std::cout << headString5;
        for (size_t j = headString5.size(); j <= maxLen5; ++j) {
            std::cout << ' ';
        }
        std::cout << ' ' << headString2;
        for (size_t j = headString2.size(); j <= maxLen2; ++j) {
            std::cout << ' ';
        }
        std::cout << '\n';
        for (size_t j = 0; j < res.size(); ++j) {
            std::cout << res[j].time;
            int beg = std::to_string(res[j].time).size();
            for (size_t k = beg; k <= maxLen5; ++k) {
                std::cout << ' ';
            }
            std::cout << ' ';
            for (size_t k = 0; k <= maxLen2; ++k) {
                if (k < res[j].log.len) {
                    std::cout << res[j].log.operation[k];
                } else {
                    std::cout << ' ';
                }
            }
            std::cout << '\n';
        }
    }
}
void LogInfoStorage::showLog() {
    std::cout << "The Log of Bookstore!\n";
    int len;
    logStorage.get_info(len, 1);
    size_t maxLen1 = headString1.size(), maxLen2 = headString2.size();
    for (size_t i = 0; i < len; ++i) {
        LogInfo tmp;
        logStorage.read(tmp, i + 1);
        maxLen1 = std::max(maxLen1, tmp.UserID.getLen());
        maxLen2 = std::max(maxLen2, (size_t)tmp.len);
    }
    std::cout << headString1;
    for (size_t i = headString1.size(); i <= maxLen1; ++i) {
        std::cout << ' ';
    }
    std::cout << ' ' << headString2;
    for (size_t i = headString2.size(); i <= maxLen2; ++i) {
        std::cout << ' ';
    }
    std::cout << '\n';
    for (size_t i = 0; i < len; ++i) {
        LogInfo tmp;
        logStorage.read(tmp, i + 1);
        std::cout << tmp.UserID;
        for (size_t i = tmp.UserID.getLen(); i <= maxLen1; ++i) {
            std::cout << ' ';
        }
        std::cout << ' ';
        for (size_t i = 0; i <= maxLen2; ++i) {
            if (i < tmp.len) {
                std::cout << tmp.operation[i];
            } else {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
}