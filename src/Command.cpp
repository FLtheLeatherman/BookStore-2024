#include <string>
#include <map>
#include <assert.h>
#include "Command.hpp"
#include "Book.hpp"
#include "Account.hpp"
#include "Log.hpp"

void Run::initialize() {
    accountStorage.initialize();
    bookStorage.initialize();
    logStorage.initialize();
}

void Run::run(std::string command) {
    Account curAccount = nowAccount;
    try {
        if (!command.length()) {
            throw Invalid();
        }
        if (command.substr(0, 3) == "su ") {
            runSu(command);
        } else if (command.substr(0, 6) == "logout") {
            runLogout(command);
        } else if (command.substr(0, 9) == "register ") {
            runRegister(command);
        } else if (command.substr(0, 7) == "passwd ") {
            runPasswd(command);
        } else if (command.substr(0, 8) == "useradd ") {
            runUseradd(command);
        } else if (command.substr(0, 7) == "delete ") {
            runDelete(command);
        } else if (command.substr(0, 4) == "buy ") {
            runBuy(command);
        } else if (command.substr(0, 7) == "select ") {
            runSelect(command);
        } else if (command.substr(0, 7) == "modify ") {
            runModify(command);
        } else if (command.substr(0, 7) == "import ") {
            runImport(command);
        } else if (command.substr(0, 13) == "show finance ") {
            runShowFinance(command);
        } else if (command.substr(0, 12) == "show finance"){
            runShowFinance(command);
        } else if (command.substr(0, 5) == "show ") {
            runShow(command);
        } else if (command.substr(0, 4) == "show") {
            runShow(command);
        } else if (command.substr(0, 14) == "report finance") {
            runReportFinance(command);
        } else if (command.substr(0, 3) == "log") {
            runLog(command);
        } else {
            throw Invalid();
        }
    } catch (const Invalid &ex) {
        std::cout << ex.what();
        std::string UserID;
        std::array<char, 400> tmp;
        tmp[0] = 'I', tmp[1] = 'n', tmp[2] = 'v', tmp[3] = 'a', tmp[4] = 'l', tmp[5] = 'i', tmp[6] = 'd';
        if (curAccount.UserID.getLen() == 0) {
            UserID = "No Login User";
            logStorage.addLog(UserID, 7, tmp);
        } else {
            logStorage.addLog(curAccount.UserID, 7, tmp);
        }
        return;
    }
    std::string UserID;
    int len = command.length();
    std::array<char, 400> tmp;
    for (size_t i = 0; i < len; ++i) {
        tmp[i] = command[i];
    }
    if (curAccount.UserID.getLen() == 0) {
        UserID = "No Login User";
        logStorage.addLog(UserID, len, tmp);
    } else {
        logStorage.addLog(curAccount.UserID, len, tmp);
    }
}

int Run::getUserID(std::string str, int pos) {
    for (int i = pos; i < str.length(); ++i) {
        if (isdigit(str[i]) || isalpha(str[i]) || (str[i] == '_')) {
            continue;
        }
        if (str[i] == ' ') {
            if (i - pos > 30) return -1;
            return i;
        } else {
            return -1;
        }
    }
    if (str.length() - pos > 30) {
        return -1;
    }
    return str.length();
}
int Run::getPassword(std::string str, int pos) {
    return getUserID(str, pos);
}
int Run::getCurrentPassword(std::string str, int pos) {
    return getUserID(str, pos);
}
int Run::getNewPassword(std::string str, int pos) {
    return getUserID(str, pos);
}
int Run::getUsername(std::string str, int pos) {
    for (int i = pos; i < str.length(); ++i) {
        if (isprint(str[i]) && str[i] != ' ') {
            continue;
        }
        if (str[i] == ' ') {
            if (i - pos > 30) return -1;
            return i;
        } else {
            return -1;
        }
    }
    if (str.length() - pos > 30) {
        return -1;
    }
    return str.length();
}
int Run::getPrivilege(std::string str, int pos) {
    for (int i = pos; i < str.length(); ++i) {
        if (str[i] == '0' || str[i] == '1' || str[i] == '3' || str[i] == '7') {
            continue;
        }
        if (str[i] == ' ') {
            if (i - pos > 1) return -1;
            return i;
        } else {
            return -1;
        }
    }
    if (str.length() - pos > 1) {
        return -1;
    }
    return str.length();
}
int Run::getISBN(std::string str, int pos) {
    for (int i = pos; i < str.length(); ++i) {
        if (isprint(str[i]) && str[i] != ' ') {
            continue;
        }
        if (str[i] == ' ') {
            if (i - pos > 20) return -1;
            return i;
        } else {
            return -1;
        }
    }
    if (str.length() - pos > 20) {
        return -1;
    }
    return str.length();
}
int Run::getBookName(std::string str, int pos) {
    for (int i = pos; i < str.length(); ++i) {
        if (isprint(str[i]) && str[i] != '\"' && str[i] != ' ') {
            continue;
        }
        if (str[i] == ' ') {
            if (i - pos > 60) return -1;
            return i;
        } else if (str[i] == '\"') {
            if (i - pos > 60) return -1;
            return -i;
        } else {
            return -1;
        }
    }
    if (str.length() - pos > 60) {
        return -1;
    }
    return str.length();
}
int Run::getAuthor(std::string str, int pos) {
    return getBookName(str, pos);
}
int Run::getKeyword(std::string str, int pos) {
    return getBookName(str, pos);
}
int Run::getQuantity(std::string str, int pos) {
    for (int i = pos; i < str.length(); ++i) {
        if (isdigit(str[i])) {
            continue;
        }
        if (str[i] == ' ') {
            if (i - pos > 10) return -1;
            return i;
        } else {
            return -1;
        }
    }
    if (str.length() - pos > 10) {
        return -1;
    }
    return str.length();
}
int Run::getPrice(std::string str, int pos) {
    int cnt = 0;
    for (int i = pos; i < str.length(); ++i) {
        if (isdigit(str[i]) || str[i] == '.') {
            if (str[i] == '.') {
                cnt++;
            }
            continue;
        }
        if (str[i] == ' ') {
            if (i - pos > 13) return -1;
            if (cnt > 1) return -1;
            return i;
        } else {
            return -1;
        }
    }
    if (str.length() - pos > 13) {
        return -1;
    }
    return str.length();
}
int Run::getTotalCost(std::string str, int pos) {
    return getPrice(str, pos);
}
int Run::getCount(std::string str, int pos) {
    for (int i = pos; i < str.length(); ++i) {
        if (isdigit(str[i])) {
            continue;
        }
        if (str[i] == ' ') {
            if (i - pos > 10) return -1;
            return i;
        } else {
            return -1;
        }
    }
    if (str.length() - pos > 10) {
        return -1;
    }
    return str.length();
}

int Run::getNumber(std::string str) {
    long long res = 0;
    for (int i = 0; i < str.length(); ++i) {
        res = res * 10ll + str[i] - '0';
    }
    if (res > 2147483647) {
        return -1;
    }
    if (str.length() > 1 && str[0] == '0') {
        return -1;
    }
    return (int)res;
}
double Run::getDouble(std::string str) {
    double res = 0;
    int pos = str.length();
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == '.') {
            pos = i;
            break;
        }
        res = res * 10 + str[i] - '0';
    }
    if (pos == 0 || pos == str.length() - 1 || str.length() - pos > 3) {
        return -1;
    }
    double base = 0.1;
    for (int i = pos + 1; i < str.length(); ++i) {
        if (str[i] == '.') {
            return -1;
        }
        res = res + (str[i] - '0') * base;
        base /= 10;
    }
    if (pos > 1 && str[0] == '0') {
        return -1;
    }
    return res;
}

const std::string preISBN = "-ISBN=";
const std::string preName = "-name=\"";
const std::string preAuthor = "-author=\"";
const std::string preKeyword = "-keyword=\"";
const std::string prePrice = "-price=";
std::pair<ParamType, int> Run::getToken(std::string str, int pos) {
    if (pos >= str.size()) {
        return std::make_pair(kError, -1);
    }
    if (str[pos] != '-') {
        return std::make_pair(kError, -1);
    }
    if (str.substr(pos, 6) == preISBN) {
        int p1 = pos + 6;
        int p2 = getISBN(str, p1);
        if (p1 == p2) {
            return std::make_pair(kError, -1);
        }
        return std::make_pair(kISBN, p2);
    }
    if (str.substr(pos, 7) == preName) {
        int p1 = pos + 7;
        int p2 = getBookName(str, p1);
        if (p2 >= -1 || p1 == -p2) {
            return std::make_pair(kError, -1);
        }
        return std::make_pair(kName, p2);
    }
    if (str.substr(pos, 9) == preAuthor) {
        int p1 = pos + 9;
        int p2 = getAuthor(str, p1);
        if (p2 >= -1 || p1 == -p2) {
            return std::make_pair(kError, -1);
        }
        return std::make_pair(kAuthor, p2);
    }
    if (str.substr(pos, 10) == preKeyword) {
        int p1 = pos + 10;
        int p2 = getKeyword(str, p1);
        if (p2 >= -1 || p1 == -p2) {
            return std::make_pair(kError, -1);
        }
        return std::make_pair(kKeyword, p2);
    }
    if (str.substr(pos, 7) == prePrice) {
        int p1 = pos + 7;
        int p2 = getPrice(str, p1);
        if (p1 == -p2) {
            return std::make_pair(kError, -1);
        }
        return std::make_pair(kPrice, p2);
    }
    return std::make_pair(kError, -1);
}

void Run::runSu(std::string command) {
    int p1 = 2;
    int p2 = getUserID(command, p1 + 1);
    if (p2 == -1) {
        throw Invalid();
    }
    if (p2 == command.length()) {
        String30 UserID = command.substr(p1 + 1, p2 - p1 - 1), Password;
        if (!accountStorage.login(UserID, Password)) {
            throw Invalid();
        }
    } else {
        int p3 = getPassword(command, p2 + 1);
        if (p3 != command.length()) {
            throw Invalid();
        }
        String30 UserID = command.substr(p1 + 1, p2 - p1 - 1), Password = command.substr(p2 + 1, p3 - p2 - 1);
        if (!accountStorage.login(UserID, Password)) {
            throw Invalid();
        }
        nowAccount = accountStorage.getAccount();
    }
}
void Run::runLogout(std::string command) {
    if (nowAccount.Privilege < 1) {
        throw Invalid();
    }
    if (!accountStorage.logout()) {
        throw Invalid();
    }
    nowAccount = accountStorage.getAccount();
    bookStorage.select(accountStorage.getSelect());
}
void Run::runRegister(std::string command) {
    int p1 = 8;
    int p2 = getUserID(command, p1 + 1);
    if (p2 == -1 || p2 == command.length()) {
        throw Invalid();
    }
    int p3 = getPassword(command, p2 + 1);
    if (p3 == -1 || p3 == command.length()) {
        throw Invalid();
    }
    int p4 = getUsername(command, p3 + 1);
    if (p4 != command.length()) {
        throw Invalid();
    }
    String30 UserID = command.substr(p1 + 1, p2 - p1 - 1);
    String30 Password = command.substr(p2 + 1, p3 - p2 - 1);
    String30 UserName = command.substr(p3 + 1, p4 - p3 - 1);
    if (!accountStorage.signup(UserID, Password, UserName)) {
        throw Invalid();
    }
}
void Run::runPasswd(std::string command) {
    if (nowAccount.Privilege < 1) {
        throw Invalid();
    }
    int p1 = 6;
    int p2 = getUserID(command, p1 + 1);
    if (p2 == -1 || p2 == command.length()) {
        throw Invalid();
    }
    int p3 = getCurrentPassword(command, p2 + 1);
    if (p3 == -1) {
        throw Invalid();
    }
    if (p3 == command.length()) {
        String30 UserID = command.substr(p1 + 1, p2 - p1 - 1);
        String30 CurrentPassword;
        String30 NewPassword = command.substr(p2 + 1, p3 - p2 - 1);
        if (!accountStorage.changePassword(UserID, CurrentPassword, NewPassword)) {
            throw Invalid();
        }
    } else {
        int p4 = getNewPassword(command, p3 + 1);
        if (p4 != command.length()) {
            throw Invalid();
        }
        String30 UserID = command.substr(p1 + 1, p2 - p1 - 1);
        String30 CurrentPassword = command.substr(p2 + 1, p3 - p2 - 1);
        String30 NewPassword = command.substr(p3 + 1, p4 - p3 - 1);
        if (!accountStorage.changePassword(UserID, CurrentPassword, NewPassword)) {
            throw Invalid();
        }
    }
}
void Run::runUseradd(std::string command) {
    if (nowAccount.Privilege < 3) {
        throw Invalid();
    }
    int p1 = 7;
    int p2 = getUserID(command, p1 + 1);
    if (p2 == -1 || p2 == command.length()) {
        throw Invalid();
    }
    int p3 = getPassword(command, p2 + 1);
    if (p3 == -1 || p3 == command.length()) {
        throw Invalid();
    }
    int p4 = getPrivilege(command, p3 + 1);
    if (p4 == -1 || p4 == command.length()) {
        throw Invalid();
    }
    int p5 = getUsername(command, p4 + 1);
    if (p5 != command.length()) {
        throw Invalid();
    }
    String30 UserID = command.substr(p1 + 1, p2 - p1 - 1);
    String30 Password = command.substr(p2 + 1, p3 - p2 - 1);
    int Privilege = command[p3 + 1] - '0';
    String30 UserName = command.substr(p4 + 1, p5 - p4 - 1);
    if (!accountStorage.useradd(UserID, Password, Privilege, UserName)) {
        throw Invalid();
    }
}
void Run::runDelete(std::string command) {
    if (nowAccount.Privilege < 7) {
        throw Invalid();
    }
    int p1 = 6;
    int p2 = getUserID(command, p1 + 1);
    if (p2 != command.length()) {
        throw Invalid();
    }
    String30 UserID = command.substr(p1 + 1, p2 - p1 - 1);
    if (!accountStorage.deleteUser(UserID)) {
        throw Invalid();
    }
}
void Run::runShow(std::string command) {
    if (nowAccount.Privilege < 1) {
        throw Invalid();
    }
    if (command.length() == 4) {
        bookStorage.show();
        return;
    }
    int p1 = 5;
    std::pair<ParamType, int> res = getToken(command, p1);
    if (res.first == kError || res.first == kPrice) {
        throw Invalid();
    }
    if (res.first == kISBN) {
        p1 += 6;
        int p2 = res.second;
        if (p2 != command.length()) {
            throw Invalid();
        }
        if (p1 > command.length()) {
            throw Invalid();
        }
        String20 ISBN = command.substr(p1, p2 - p1);
        bookStorage.showISBN(ISBN);
    } else if (res.first == kName) {
        p1 += 7;
        int p2 = res.second;
        p2 = -p2;
        if (p2 + 1 != command.length()) {
            throw Invalid();
        }
        if (p1 > command.length()) {
            throw Invalid();
        }
        String60 BookName = command.substr(p1, p2 - p1);
        bookStorage.showBookName(BookName);
    } else if (res.first == kAuthor) {
        p1 += 9;
        int p2 = res.second;
        p2 = -p2;
        if (p2 + 1 != command.length()) {
            throw Invalid();
        }
        if (p1 > command.length()) {
            throw Invalid();
        }
        String60 Author = command.substr(p1, p2 - p1);
        bookStorage.showAuthor(Author);
    } else if (res.first == kKeyword) {
        p1 += 10;
        int p2 = res.second;
        p2 = -p2;
        if (p2 + 1 != command.length() || p2 == p1) {
            throw Invalid();
        }
        if (p1 > command.length()) {
            throw Invalid();
        }
        String60 Keyword = command.substr(p1, p2 - p1);
        if (!bookStorage.showKeyword(Keyword)) {
            throw Invalid();
        }
    }
}
void Run::runBuy(std::string command) {
    if (nowAccount.Privilege < 1) {
        throw Invalid();
    }
    int p1 = 3;
    int p2 = getISBN(command, p1 + 1);
    if (p2 == -1 || p2 == command.length()) {
        throw Invalid();
    }
    int p3 = getQuantity(command, p2 + 1);
    if (p3 != command.length()) {
        throw Invalid();
    }
    std::string quantity = command.substr(p2 + 1, p3 - p2 - 1);
    int Quantity = getNumber(quantity);
    if (Quantity <= 0) {
        throw Invalid();
    }
    String20 ISBN = command.substr(p1 + 1, p2 - p1 - 1);
    double income = bookStorage.buy(ISBN, Quantity);
    if (income < 0) {
        throw Invalid();
    }

    std::string Income = std::to_string(income);
    Income = Income.substr(0, Income.size() - 4);
    std::string tmp;
    tmp = "buy " + quantity + " book" + (Quantity > 1 ? "s" : "") + " with ISBN = " + command.substr(p1 + 1, p2 - p1 - 1) + " and cost = " + Income;
    int len = tmp.length();
    std::array<char, 400> operation;
    for (size_t i = 0; i < len; ++i) {
        operation[i] = tmp[i];
    }
    logStorage.addFinance(income, 0, nowAccount.UserID, len, operation);
}
void Run::runSelect(std::string command) {
    if (nowAccount.Privilege < 3) {
        throw Invalid();
    }
    int p1 = 6;
    int p2 = getISBN(command, p1 + 1);
    if (p2 != command.length() || p2 == p1 + 1) {
        throw Invalid();
    }
    String20 ISBN = command.substr(p1 + 1, p2 - p1 - 1);
    int cur = bookStorage.select(ISBN);
    accountStorage.select(cur);
}
void Run::runModify(std::string command) {
    if (nowAccount.Privilege < 3) {
        throw Invalid();
    }
    static bool vis[5];
    vis[0] = vis[1] = vis[2] = vis[3] = vis[4] = false;
    static std::map<std::string, bool> mp;
    mp.clear();
    int p1 = 7;
    std::vector<std::pair<ParamType, std::pair<int, int>>> vec(4);
    double Price;
    while (p1 < command.length()) {
        if (command[p1 - 1] != ' ') {
            throw Invalid();
        }
        std::pair<ParamType, int> res = getToken(command, p1);
        if (res.first == kError) {
            throw Invalid();
        }
        if (res.first == kISBN) {
            if (vis[0]) {
                throw Invalid();
            }
            vis[0] = true;
            p1 += 6;
            int p2 = res.second;
            if (p2 == p1 || p2 == -1) {
                throw Invalid();
            }
            vec[0] = std::make_pair(kISBN, std::make_pair(p1, p2));
            p1 = p2 + 1;
        } else if (res.first == kName) {
            if (vis[1]) {
                throw Invalid();
            }
            vis[1] = true;
            p1 += 7;
            int p2 = res.second;
            p2 = -p2;
            if (p2 == p1 || p2 == 1) {
                throw Invalid();
            }
            vec[1] = std::make_pair(kName, std::make_pair(p1, p2));
            p1 = p2 + 2;
        } else if (res.first == kAuthor) {
            if (vis[2]) {
                throw Invalid();
            }
            vis[2] = true;
            p1 += 9;
            int p2 = res.second;
            p2 = -p2;
            if (p2 == p1 || p2 == 1) {
                throw Invalid();
            }
            vec[2] = std::make_pair(kAuthor, std::make_pair(p1, p2));
            p1 = p2 + 2;
        } else if (res.first == kKeyword) {
            if (vis[3]) {
                throw Invalid();
            }
            vis[3] = true;
            p1 += 10;
            int p2 = res.second;
            p2 = -p2;
            if (p2 == p1 || p2 == 1) {
                throw Invalid();
            }
            if (p1 > command.length()) {
                throw Invalid();
            }
            std::string tmp = "";
            for (int i = p1; i < p2; ++i) {
                if (command[i] == '|') {
                    if (tmp.length() == 0) {
                        throw Invalid();
                    }
                    if (mp[tmp]) {
                        throw Invalid();
                    }
                    mp[tmp] = true;
                    tmp = "";
                } else {
                    tmp += command[i];
                }
            }
            if (tmp.length() == 0) {
                throw Invalid();
            }
            if (mp[tmp]) {
                throw Invalid();
            }
            mp[tmp] = true;
            vec[3] = std::make_pair(kKeyword, std::make_pair(p1, p2));
            p1 = p2 + 2;
        } else {
            if (vis[4]) {
                throw Invalid();
            }
            vis[4] = true;
            p1 += 7;
            int p2 = res.second;
            if (p1 > command.length()) {
                throw Invalid();
            }
            std::string price = command.substr(p1, p2 - p1);
            Price = getDouble(price);
            if (Price < 0) {
                throw Invalid();
            }
            p1 = p2 + 1;
        }
    }
    if (p1 != command.length() + 1) {
        throw Invalid();
    }
    if (vis[0]) {
        if (vec[0].second.first > command.length()) {
            throw Invalid();
        }
        String20 ISBN = command.substr(vec[0].second.first, vec[0].second.second - vec[0].second.first);
        if (!bookStorage.modifyISBN(ISBN)) {
            throw Invalid();
        }
    }
    for (int i = 1; i < 4; ++i) {
        if (vis[i]) {
            auto now = vec[i];
            if (now.second.first > command.length()) {
                throw Invalid();
            }
            String60 tmp = command.substr(now.second.first, now.second.second - now.second.first);
            if (now.first == kName) {
                if (!bookStorage.modifyBookName(tmp)) {
                    throw Invalid();
                }
            } else if (now.first == kAuthor) {
                if (!bookStorage.modifyAuthor(tmp)) {
                    throw Invalid();
                }
            } else {
                if (!bookStorage.modifyKeyword(tmp)) {
                    throw Invalid();
                }
            }
        }
    }
    if (vis[4]) {
        if (!bookStorage.modifyPrice(Price)) {
            throw Invalid();
        }
    }
}
void Run::runImport(std::string command) {
    if (nowAccount.Privilege < 3) {
        throw Invalid();
    }
    int p1 = 6;
    int p2 = getQuantity(command, p1 + 1);
    if (p2 == -1 || p2 == command.length()) {
        throw Invalid();
    }
    int p3 = getTotalCost(command, p2 + 1);
    if (p3 != command.length()) {
        throw Invalid();
    }
    std::string quantity = command.substr(p1 + 1, p2 - p1 - 1), totalCost = command.substr(p2 + 1, p3 - p2 - 1);
    int Quantity = getNumber(quantity);
    double TotalCost = getDouble(totalCost);
    if (Quantity <= 0 || TotalCost <= 0) {
        throw Invalid();
    }
    if (!bookStorage.import(Quantity)) {
        throw Invalid();
    }
    std::string tmp;
    tmp = "import " + quantity + " book" + (Quantity > 1 ? "s" : "") + " with ISBN = " + command.substr(p1 + 1, p2 - p1 - 1) + " and cost = " + totalCost;
    int len = tmp.length();
    std::array<char, 400> operation;
    for (size_t i = 0; i < len; ++i) {
        operation[i] = tmp[i];
    }
    logStorage.addFinance(0, TotalCost, nowAccount.UserID, len, operation);
}
void Run::runShowFinance(std::string command) {
    if (nowAccount.Privilege < 7) {
        throw Invalid();
    }
    if (command.length() == 12) {
        if (!logStorage.showFinance(-1)) {
            throw Invalid();
        }
        return;
    }
    int p1 = 12;
    int p2 = getCount(command, p1 + 1);
    if (p2 != command.length()) {
        throw Invalid();
    }
    std::string count = command.substr(p1 + 1, p2 - p1 - 1);
    int number = getNumber(count);
    if (number < 0) {
        throw Invalid();
    }
    if (!logStorage.showFinance(number)) {
        throw Invalid();
    }
}
void Run::runReportFinance(std::string command) {
    if (nowAccount.Privilege < 7) {
        throw Invalid();
    }
    logStorage.showFinanceInfo();
}
void Run::runLog(std::string command) {
    if (nowAccount.Privilege < 7) {
        throw Invalid();
    }
    logStorage.showLog();
}