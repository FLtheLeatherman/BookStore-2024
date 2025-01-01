#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include "Account.hpp"
#include "Book.hpp"
#include "Log.hpp"

enum ParamType {
    kISBN, kName, kAuthor, kKeyword, kPrice, kError
};

class Invalid : std::exception {
public:
    const char *what() const noexcept override {
        return "Invalid\n";
    }
};

class Run {
private:
    AccountStorage accountStorage;
    BookStorage bookStorage;
    LogInfoStorage logStorage;
    Account nowAccount;
public:
    void initialize();
    ~Run() = default;

    void run(std::string);

    int getUserID(std::string, int);
    int getPassword(std::string, int);
    int getCurrentPassword(std::string, int);
    int getNewPassword(std::string, int);
    int getUsername(std::string, int);
    int getPrivilege(std::string, int);
    int getISBN(std::string, int);
    int getBookName(std::string, int);
    int getAuthor(std::string, int);
    int getKeyword(std::string, int);
    int getQuantity(std::string, int);
    int getPrice(std::string, int);
    int getTotalCost(std::string, int);
    int getCount(std::string, int);

    int getNumber(std::string);
    double getDouble(std::string);

    std::pair<ParamType, int> getToken(std::string, int);

    void runSu(std::string);
    void runLogout(std::string);
    void runRegister(std::string);
    void runPasswd(std::string);
    void runUseradd(std::string);
    void runDelete(std::string);
    void runShow(std::string);
    void runBuy(std::string);
    void runSelect(std::string);
    void runModify(std::string);
    void runImport(std::string);
    void runShowFinance(std::string);
    void runReportFinance(std::string);
    void runLog(std::string);
};

#endif