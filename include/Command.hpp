#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include "Account.hpp"
#include "Book.hpp"
#include "Log.hpp"

enum ParamType {
    kISBN, kName, kAuthor, kKeyword, kPrice, kError
};

class Run {
private:
    AccountStorage as;
    BookStorage bs;
    LogInfoStorage ls;
    Account nowAccount;
public:
    void initialize();
    ~Run() = default;

    void invalid();

    void format(std::string &);

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
};

#endif