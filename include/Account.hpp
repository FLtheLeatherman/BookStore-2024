#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <array>
#include <string>
#include <vector>
#include "BlockList.hpp"
#include "Book.hpp"

class String30 {
private:
    const static int maxLen = 30;
    size_t len;
    std::array<char, 30> str;
public:
    String30();
    String30(std::string);
    String30(std::array<char, 30>, size_t);
    size_t getLen();
    std::array<char, 30> getValue();
    bool operator <(const String30 &);
    bool operator ==(const String30 &);
    String30 &operator = (const String30 &);
    friend std::ostream& operator <<(std::ostream &, const String30 &);
};

class Account {
public:
    String30 UserID, Password, Username;
    int Privilege;
    Account();
    Account(String30 UserID, String30 Password, String30 Username, int Privilege);
    bool operator <(const Account &);
    bool operator ==(const Account &);
    friend std::ostream& operator <<(std::ostream &, const Account &);
};

class AccountStorage {
private:
    BlockList<String30, Account> blockList;
    std::vector<std::pair<Account, Book>> userStack;
public:
    void initialize();
    ~AccountStorage() = default;
    void select(Book book);
    Book getSelect();
    bool login(String30 UserID, String30 Password);
    bool logout();
    bool signup(String30 UserID, String30 Password, String30 Username);
    bool changePassword(String30 UserID, String30 CurrentPassword, String30 NewPassword);
    bool useradd(String30 UserID, String30 Password, int Privilege, String30 Username);
    bool deleteUser(String30 UserID);
};

#endif