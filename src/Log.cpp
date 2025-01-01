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


void LogInfoStorage::initialize() {
    financeStorage.initialize("Finance");
    financeInfoStorage.initialize("FinanceInfo");
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