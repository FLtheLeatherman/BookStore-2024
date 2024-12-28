#include <iostream>
#include "Log.hpp"

LogInfo::LogInfo() {
    income = expend = 0;
}
LogInfo::LogInfo(double income, double expend) {
    this->income = income;
    this->expend = expend;
}
bool LogInfo::operator <(const LogInfo& RHS) {
    return true;
}
bool LogInfo::operator ==(const LogInfo& RHS) {
    return true;
}
std::ostream& operator <<(std::ostream &out, const LogInfo& logInfo) {
    out << logInfo.income << ' ' << logInfo.expend;
    return out;
}

void LogInfoStorage::initialize() {
    storage.initialize("LogInfo");
}
void LogInfoStorage::addLog(double income, double expend) {
    int len;
    LogInfo lst;
    storage.get_info(len, 1);
    storage.read(lst, len);
    len++;
    lst.income += income, lst.expend += expend;
    storage.write_info(len, 1);
    storage.write(lst, len);
}
bool LogInfoStorage::showFinance(int Count) {
    int len;
    storage.get_info(len, 1);
    if (Count > len) {
        return false;
    }
    if (!Count) {
        std::cout << '\n';
    } else {
        if (Count == len) {
            LogInfo tmp;
            storage.read(tmp, len);
            std::cout << "+ " << tmp.income << " - " << tmp.expend << '\n';
        } else {
            LogInfo tmp1, tmp2;
            storage.read(tmp1, len);
            storage.read(tmp2, len - Count);
            tmp1.income -= tmp2.income;
            tmp1.expend -= tmp2.expend;
            std::cout << "+ " << tmp1.income << " - " << tmp1.expend << '\n';
        }
    }
    return true;
}