#include "Account.hpp"

String30::String30() {
    len = 0;
}
String30::String30(std::string str) {
    len = str.length();
    for (int i = 0; i < len; ++i) {
        this->str[i] = str[i];
    }
}
String30::String30(std::array<char, 30> arr, size_t len) {
    this->len = len;
    for (int i = 0; i < len; ++i) {
        this->str[i] = arr[i];
    }
}
size_t String30::getLen() {
    return len;
}
std::array<char, 30> String30::getValue() {
    return str;
}
bool String30::operator <(const String30& RHS) {
    size_t L = std::min(this->len, RHS.len);
    for (int i = 0; i < L; ++i) {
        if (this->str[i] < RHS.str[i]) {
            return true;
        } else if (this->str[i] > RHS.str[i]) {
            return false;
        }
    }
    if (this->len < RHS.len) {
        return true;
    } else {
        return false;
    }
}
bool String30::operator ==(const String30& RHS) {
    if (this->len != RHS.len) {
        return false;
    }
    for (int i = 0; i < this->len; ++i) {
        if (this->str[i] != RHS.str[i]) {
            return false;
        }
    }
    return true;
}
String30 &String30::operator = (const String30 &RHS) {
    if (this == &RHS) {
        return (*this);
    }
    this->len = RHS.len;
    for (int i = 0; i < len; ++i) {
        this->str[i] = RHS.str[i];
    }
    return (*this);
}
std::ostream& operator <<(std::ostream &out, const String30 &str) {
    for (int i = 0; i < str.len; ++i) {
        out << str.str[i];
    }
    return out;
}

Account::Account() {
    UserID = String30();
}
Account::Account(String30 UserID, String30 Password, String30 Username, int Privilege) {
    this->UserID = UserID;
    this->Password = Password;
    this->Username = Username;
    this->Privilege = Privilege;
}
bool Account::operator <(const Account &RHS) {
    return this->UserID < RHS.UserID;
}
bool Account::operator ==(const Account &RHS) {
    return this->UserID == RHS.UserID;
}
std::ostream& operator <<(std::ostream &out, const Account &account) {
    out << account.UserID;
    return out;
} // 实际上似乎并不用实现这个函数。不过便于调试（和通过编译）还是写了。

void AccountStorage::select(Book book) {
    userStack.back().second = book;
}
Book AccountStorage::getSelect() {
    return userStack.back().second;
}
bool AccountStorage::login(String30 UserID, String30 Password) {
    std::vector<Account> res = blockList.query(UserID);
    if (res.empty()) {
        return false;
    }
    if (Password.getLen() > 0) {
        if (!(Password == res[0].Password)) {
            return false;
        }
    } else {
        if (userStack.back().first.Privilege <= res[0].Privilege) {
            return false;
        }
    }
    userStack.push_back(std::make_pair(res[0], Book()));
    return true;
}
bool AccountStorage::logout() {
    if (userStack.empty()) {
        return false;
    }
    userStack.pop_back();
    return true;
}
bool AccountStorage::signup(String30 UserID, String30 Password, String30 Username) {
    std::vector<Account> res = blockList.query(UserID);
    if (!res.empty()) {
        return false;
    }
    Account newAccount(UserID, Password, Username, 1);
    blockList.insert(UserID, newAccount);
    return true;
}
bool AccountStorage::changePassword(String30 UserID, String30 CurrentPassword, String30 NewPassword) {
    std::vector<Account> res = blockList.query(UserID);
    if(res.empty()) {
        return false;
    }
    if (CurrentPassword.getLen() > 0) {
        if (!(CurrentPassword == res[0].Password)) {
            return false;
        }
    } else {
        if (userStack.empty() || userStack.back().first.Privilege < 7) {
            return false;
        }
    }
    blockList.mydelete(UserID, res[0]);
    res[0].Password = NewPassword;
    blockList.insert(UserID, res[0]);
    return true;
}
bool AccountStorage::useradd(String30 UserID, String30 Password, int Privilege, String30 Username) {
    if (userStack.empty() || userStack.back().first.Privilege <= Privilege) {
        return false;
    }
    std::vector<Account> res = blockList.query(UserID);
    if (!res.empty()) {
        return false;
    }
    Account newAccount(UserID, Password, Username, Privilege);
    blockList.insert(UserID, newAccount);
    return true;
}
bool AccountStorage::deleteadd(String30 UserID) {
    std::vector<Account> res = blockList.query(UserID);
    if (res.empty()) {
        return false;
    }
    bool inStack = false;
    for (size_t i = 0; i < userStack.size(); ++i) {
        if (res[0] == userStack[i].first) {
            inStack = true;
            break;
        }
    }
    if (inStack) {
        return false;
    }
    blockList.mydelete(res[0].UserID, res[0]);
    return true;
}