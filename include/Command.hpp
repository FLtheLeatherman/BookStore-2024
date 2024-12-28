#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class Run {
public:
    static void invalid();

    static void run(std::string);

    static int getUserID(std::string, int);
    static int getPassword(std::string, int);
    static int getCurrentPassword(std::string, int);
    static int getNewPassword(std::string, int);
    static int getUsername(std::string, int);
    static int getPrivilege(std::string, int);
    static int getISBN(std::string, int);
    static int getBookName(std::string, int);
    static int getAuthor(std::string, int);
    static int getKeyword(std::string, int);
    static int getQuantity(std::string, int);
    static int getPrice(std::string, int);
    static int getTotalCost(std::string, int);
    static int getCount(std::string, int);

    static void runSu(std::string);
    static void runLogout(std::string);
    static void runRegister(std::string);
    static void runPasswd(std::string);
    static void runUseradd(std::string);
    static void runDelete(std::string);
    static void runShow(std::string);
    static void runBuy(std::string);
    static void runSelect(std::string);
    static void runModify(std::string);
    static void runImport(std::string);
    static void runShowFinance(std::string);
};

#endif