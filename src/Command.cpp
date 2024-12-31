#include <string>
#include <map>
#include "Command.hpp"
#include "Book.hpp"
#include "Account.hpp"
#include "Log.hpp"

void Run::initialize() {
    as.initialize();
    bs.initialize();
    ls.initialize();
}

void Run::invalid() {
    std::cout << "Invalid" << std::endl;
}

void Run::format(std::string &str) {
    std::string tmp = "";
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] != ' ') {
            tmp += str[i];
        } else {
            int p = i;
            while (p + 1 < str.length() && str[p + 1] == ' ') {
                p++;
            }
            if (i != 0 && p != str.length() - 1) {
                tmp += ' ';
            }
            i = p;
        }
    }
    str = tmp;
}

void Run::run(std::string command) {
    try {
        format(command);
        // std::cout << command.length() << std::endl;
        if (!command.length()) {
            invalid();
            return;
        }
        if (command.substr(0, 3) == "su ") {
            // std::cerr << "SIUUUUU" << std::endl;
            // invalid();
            // return;
            runSu(command);
        } else if (command.substr(0, 6) == "logout") {
            // invalid();
            // return;
            runLogout(command);
        } else if (command.substr(0, 9) == "register ") {
            // invalid();
            // return;
            runRegister(command);
        } else if (command.substr(0, 7) == "passwd ") {
            // invalid();
            // return;
            runPasswd(command);
        } else if (command.substr(0, 8) == "useradd ") {
            // invalid();
            // return;
            runUseradd(command);
        } else if (command.substr(0, 7) == "delete ") {
            // invalid();
            // return;
            runDelete(command);
        } else if (command.substr(0, 4) == "buy ") {
            // int a = 1/0;
            runBuy(command);
        } else if (command.substr(0, 7) == "select ") {
            // int a = 1/0;
            runSelect(command);
        } else if (command.substr(0, 7) == "modify ") {
            // int a = 1/0;
            runModify(command);
        } else if (command.substr(0, 7) == "import ") {
            // int a = 1/0;
            runImport(command);
        } else if (command.substr(0, 13) == "show finance ") {
            // int a = 1/0;
            runShowFinance(command);
        } else if (command.substr(0, 12) == "show finance"){
            // int a = 1/0;
            runShowFinance(command);
        }  else if (command.substr(0, 5) == "show ") {
            // int a = 1/0;
            runShow(command);
        }else if (command.substr(0, 4) == "show") {
            // int a = 1/0;
            runShow(command);
        } else {
            // int a = 1/0;
            invalid();
        }
    } catch (...) {
        throw;
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
            return -i;
        } else {
            return -1;
        }
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
    // std::cout << '&' << str.substr(pos, 7) << std::endl;
    // std::cout << '#' << preName << std::endl;
    // std::cout << (str.substr(pos, 7) == preName) << std::endl;
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
        // std::cout << '!' << p1 << ' ' << p2 << std::endl;
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
    try {
        int p1 = 2;
        int p2 = getUserID(command, p1 + 1);
        if (p2 == -1) {
            invalid();
            return;
        }
        if (p1 == command.length()) {
            invalid();
            return;
        }
        if (p2 == command.length()) {
            String30 UserID = command.substr(p1 + 1, p2 - p1 - 1), Password;
            if (!as.login(UserID, Password)) {
                invalid();
                return;
            }
        } else {
            int p3 = getPassword(command, p2 + 1);
            if (p3 != command.length()) {
                invalid();
                return;
            }
            String30 UserID = command.substr(p1 + 1, p2 - p1 - 1), Password = command.substr(p2 + 1, p3 - p2 - 1);
            if (!as.login(UserID, Password)) {
                invalid();
                return;
            }
            nowAccount = as.getAccount();
        }
    } catch (...) {
        throw;
    }
}
void Run::runLogout(std::string command) {
    try {
        if (nowAccount.Privilege < 1) {
            invalid();
            return;
        }
        if (!as.logout()) {
            invalid();
            return;
        }
        nowAccount = as.getAccount();
        bs.select(as.getSelect());
    } catch (...) {
        throw;
    }
}
void Run::runRegister(std::string command) {
    try {
        int p1 = 8;
        int p2 = getUserID(command, p1 + 1);
        if (p2 == -1 || p2 == command.length()) {
            invalid();
            return;
        }
        int p3 = getPassword(command, p2 + 1);
        if (p3 == -1 || p3 == command.length()) {
            invalid();
            return;
        }
        int p4 = getUsername(command, p3 + 1);
        if (p4 != command.length()) {
            invalid();
            return;
        }
        if (p1 == command.length()) {
            invalid();
            return;
        }
        String30 UserID = command.substr(p1 + 1, p2 - p1 - 1);
        String30 Password = command.substr(p2 + 1, p3 - p2 - 1);
        String30 UserName = command.substr(p3 + 1, p4 - p3 - 1);
        // std::cout << UserID << ' ' << Password << ' ' << UserName << std::endl;
        if (!as.signup(UserID, Password, UserName)) {
            invalid();
            return;
        }
    } catch (...) {
        throw;
    }
}
void Run::runPasswd(std::string command) {
    try {
        if (nowAccount.Privilege < 1) {
            invalid();
            return;
        }
        int p1 = 6;
        if (p1 == command.length()) {
            invalid();
            return;
        }
        int p2 = getUserID(command, p1 + 1);
        if (p2 == -1 || p2 == command.length()) {
            invalid();
            return;
        }
        int p3 = getCurrentPassword(command, p2 + 1);
        if (p3 == -1) {
            invalid();
            return;
        }
        if (p3 == command.length()) {
            String30 UserID = command.substr(p1 + 1, p2 - p1 - 1);
            String30 CurrentPassword;
            String30 NewPassword = command.substr(p2 + 1, p3 - p2 - 1);
            if (!as.changePassword(UserID, CurrentPassword, NewPassword)) {
                // std::cout << "!" << std::endl;
                invalid();
                return;
            }
        } else {
            int p4 = getNewPassword(command, p3 + 1);
            if (p4 != command.length()) {
                invalid();
                return;
            }
            String30 UserID = command.substr(p1 + 1, p2 - p1 - 1);
            String30 CurrentPassword = command.substr(p2 + 1, p3 - p2 - 1);
            String30 NewPassword = command.substr(p3 + 1, p4 - p3 - 1);
            if (!as.changePassword(UserID, CurrentPassword, NewPassword)) {
                invalid();
                return;
            }
        }
    } catch (...) {
        throw;
    }
}
void Run::runUseradd(std::string command) {
    try {
        if (nowAccount.Privilege < 3) {
            invalid();
            return;
        }
        int p1 = 7;
        int p2 = getUserID(command, p1 + 1);
        if (p2 == -1 || p2 == command.length()) {
            invalid();
            return;
        }
        int p3 = getPassword(command, p2 + 1);
        if (p3 == -1 || p3 == command.length()) {
            invalid();
            return;
        }
        int p4 = getPrivilege(command, p3 + 1);
        if (p4 == -1 || p4 == command.length()) {
            invalid();
            return;
        }
        int p5 = getUsername(command, p4 + 1);
        if (p5 != command.length()) {
            invalid();
            return;
        }
        if (p1 == command.length()) {
            invalid();
            return;
        }
        String30 UserID = command.substr(p1 + 1, p2 - p1 - 1);
        String30 Password = command.substr(p2 + 1, p3 - p2 - 1);
        int Privilege = command[p3 + 1] - '0';
        String30 UserName = command.substr(p4 + 1, p5 - p4 - 1);
        if (!as.useradd(UserID, Password, Privilege, UserName)) {
            invalid();
            return;
        }
    } catch (...) {
        throw;
    }
}
void Run::runDelete(std::string command) {
    try {
        if (nowAccount.Privilege < 7) {
            invalid();
            return;
        }
        int p1 = 6;
        int p2 = getUserID(command, p1 + 1);
        if (p2 != command.length()) {
            invalid();
            return;
        }
        if (p1 == command.length()) {
            invalid();
            return;
        }
        String30 UserID = command.substr(p1 + 1, p2 - p1 - 1);
        if (!as.deleteUser(UserID)) {
            invalid();
            return;
        }
    } catch (...) {
        throw;
    }
}
void Run::runShow(std::string command) {
    // std::cout << "!" << command << std::endl;
    if (nowAccount.Privilege < 1) {
        invalid();
        return;
    }
    // std::cout << command.length() << std::endl;
    if (command.length() == 4) {
        bs.show();
        return;
    }
    int p1 = 5;
    std::pair<ParamType, int> res = getToken(command, p1);
    if (res.first == kError || res.first == kPrice) {
        // std::cout << "huh?" << std::endl;
        invalid();
        return;
    }
    if (res.first == kISBN) {
        // std::cout << "GOOD" << std::endl;
        p1 += 6;
        int p2 = res.second;
        if (p2 != command.length()) {
            invalid();
            return;
        }
        if (p1 > command.length()) {
            invalid();
            return;
        }
        String20 ISBN = command.substr(p1, p2 - p1);
        bs.showISBN(ISBN);
    } else if (res.first == kName) {
        p1 += 7;
        int p2 = res.second;
        p2 = -p2;
        if (p2 + 1 != command.length()) {
            invalid();
            return;
        }
        if (p1 > command.length()) {
            invalid();
            return;
        }
        String60 BookName = command.substr(p1, p2 - p1);
        bs.showBookName(BookName);
    } else if (res.first == kAuthor) {
        p1 += 9;
        int p2 = res.second;
        p2 = -p2;
        if (p2 + 1 != command.length()) {
            invalid();
            return;
        }
        if (p1 > command.length()) {
            invalid();
            return;
        }
        String60 Author = command.substr(p1, p2 - p1);
        bs.showAuthor(Author);
    } else if (res.first == kKeyword) {
        p1 += 10;
        int p2 = res.second;
        p2 = -p2;
        if (p2 + 1 != command.length() || p2 == p1) {
            invalid();
            return;
        }
        if (p1 > command.length()) {
            invalid();
            return;
        }
        String60 Keyword = command.substr(p1, p2 - p1);
        if (!bs.showKeyword(Keyword)) {
            invalid();
            return;
        }
    }
}
void Run::runBuy(std::string command) {
    int p1 = 3;
    int p2 = getISBN(command, p1 + 1);
    if (p2 == -1 || p2 == command.length()) {
        invalid();
        return;
    }
    int p3 = getQuantity(command, p2 + 1);
    if (p3 != command.length()) {
        invalid();
        return;
    }
    std::string quantity = command.substr(p2 + 1, p3 - p2 - 1);
    int Quantity = getNumber(quantity);
    if (Quantity <= 0) {
        invalid();
        return;
    }
    if (p1 == command.length()) {
        invalid();
        return;
    }
    String20 ISBN = command.substr(p1 + 1, p2 - p1 - 1);
    double income = bs.buy(ISBN, Quantity);
    if (income < 0) {
        invalid();
        return;
    }
    ls.addLog(income, 0);
}
void Run::runSelect(std::string command) {
    if (nowAccount.Privilege < 3) {
        invalid();
        return;
    }
    int p1 = 6;
    int p2 = getISBN(command, p1 + 1);
    if (p2 != command.length() || p2 == p1 + 1) {
        invalid();
        return;
    }
    if (p1 == command.length()) {
        invalid();
        return;
    }
    String20 ISBN = command.substr(p1 + 1, p2 - p1 - 1);
    int cur = bs.select(ISBN);
    as.select(cur);
}
void Run::runModify(std::string command) {
    // std::cout << "?!!!!" << std::endl;
    if (nowAccount.Privilege < 3) {
        // std::cout << "?!" << std::endl;
        invalid();
        return;
    }
    static bool vis[5];
    vis[0] = vis[1] = vis[2] = vis[3] = vis[4] = false;
    static std::map<std::string, bool> mp;
    mp.clear();
    int p1 = 7;
    std::vector<std::pair<ParamType, std::pair<int, int>>> vec(4);
    double Price;
    while (p1 < command.length()) {
        std::pair<ParamType, int> res = getToken(command, p1);
        if (res.first == kError) {
            // std::cout << '?' << std::endl;
            invalid();
            return;
        }
        if (res.first == kISBN) {
            // std::cout << "isbn" << std::endl;
            if (vis[0]) {
                invalid();
                return;
            }
            vis[0] = true;
            p1 += 6;
            int p2 = res.second;
            if (p2 == p1 || p2 == -1) {
                invalid();
                return;
            }
            vec[0] = std::make_pair(kISBN, std::make_pair(p1, p2));
            p1 = p2 + 1;
        } else if (res.first == kName) {
            // std::cout << "name" << std::endl;
            if (vis[1]) {
                invalid();
                return;
            }
            vis[1] = true;
            p1 += 7;
            int p2 = res.second;
            p2 = -p2;
            if (p2 == p1 || p2 == 1) {
                invalid();
                return;
            }
            vec[1] = std::make_pair(kName, std::make_pair(p1, p2));
            p1 = p2 + 2;
        } else if (res.first == kAuthor) {
            // std::cout << "author" << std::endl;
            if (vis[2]) {
                invalid();
                return;
            }
            vis[2] = true;
            p1 += 9;
            int p2 = res.second;
            p2 = -p2;
            if (p2 == p1 || p2 == 1) {
                invalid();
                return;
            }
            vec[2] = std::make_pair(kAuthor, std::make_pair(p1, p2));
            p1 = p2 + 2;
        } else if (res.first == kKeyword) {
            // std::cout << "keyword" << std::endl;
            if (vis[3]) {
                invalid();
                return;
            }
            vis[3] = true;
            p1 += 10;
            int p2 = res.second;
            p2 = -p2;
            // std::cout << p1 << ' ' << p2 << std::endl;
            if (p2 == p1 || p2 == 1) {
                invalid();
                return;
            }
            if (p1 > command.length()) {
                invalid();
                return;
            }
            std::string tmp = "";
            for (int i = p1; i < p2; ++i) {
                if (command[i] == '|') {
                    // std::cout << tmp << std::endl;
                    if (tmp.length() == 0) {
                        invalid();
                        return;
                    }
                    if (mp[tmp]) {
                        invalid();
                        return;
                    }
                    mp[tmp] = true;
                    tmp = "";
                } else {
                    tmp += command[i];
                }
            }
            // std::cout << tmp << std::endl;
            if (tmp.length() == 0) {
                invalid();
                return;
            }
            if (mp[tmp]) {
                invalid();
                return;
            }
            mp[tmp] = true;
            vec[3] = std::make_pair(kKeyword, std::make_pair(p1, p2));
            p1 = p2 + 2;
        } else {
            // std::cout << "price" << std::endl;
            if (vis[4]) {
                invalid();
                return;
            }
            vis[4] = true;
            p1 += 7;
            int p2 = res.second;
            if (p1 > command.length()) {
                invalid();
                return;
            }
            std::string price = command.substr(p1, p2 - p1);
            Price = getDouble(price);
            if (Price < 0) {
                invalid();
                return;
            }
            p1 = p2 + 1;
        }
    }
    // std::cout << vis[0] << ' ' << vis[1] << ' ' << vis[2] << ' ' << vis[3] << ' ' << vis[4] << std::endl;
    if (vis[0]) {
        if (vec[0].second.first > command.length()) {
            invalid();
            return;
        }
        String20 ISBN = command.substr(vec[0].second.first, vec[0].second.second - vec[0].second.first);
        // std::cout << "ISBN: " << ISBN << std::endl;
        if (!bs.modifyISBN(ISBN)) {
            invalid();
            return;
        }
    }
    for (int i = 1; i < 4; ++i) {
        if (vis[i]) {
            auto now = vec[i];
            if (now.second.first > command.length()) {
                invalid();
                return;
            }
            String60 tmp = command.substr(now.second.first, now.second.second - now.second.first);
            if (now.first == kName) {
                // std::cout << "Name: " << tmp << std::endl;
                if (!bs.modifyBookName(tmp)) {
                    invalid();
                    return;
                }
            } else if (now.first == kAuthor) {
                // std::cout << "Author: " << tmp << std::endl;
                if (!bs.modifyAuthor(tmp)) {
                    invalid();
                    return;
                }
            } else {
                // std::cout << "Keyword: " << tmp << std::endl;
                if (!bs.modifyKeyword(tmp)) {
                    invalid();
                    return;
                }
            }
        }
    }
    if (vis[4]) {
        // std::cout << "Price: " << Price << std::endl;
        if (!bs.modifyPrice(Price)) {
            invalid();
            return;
        }
    }
}
void Run::runImport(std::string command) {
    if (nowAccount.Privilege < 3) {
        invalid();
        return;
    }
    int p1 = 6;
    int p2 = getQuantity(command, p1 + 1);
    // std::cout << p2 << std::endl;
    if (p2 == -1 || p2 == command.length()) {
        invalid();
        return;
    }
    int p3 = getTotalCost(command, p2 + 1);
    // std::cout << p3 << std::endl;
    if (p3 != command.length()) {
        invalid();
        return;
    }
    if (p1 == command.length()) {
        invalid();
        return;
    }
    std::string quantity = command.substr(p1 + 1, p2 - p1 - 1), totalCost = command.substr(p2 + 1, p3 - p2 - 1);
    // std::cout << quantity << ' ' << totalCost << std::endl;
    int Quantity = getNumber(quantity);
    double TotalCost = getDouble(totalCost);
    if (Quantity <= 0 || TotalCost <= 0) {
        invalid();
        return;
    }
    if (!bs.import(Quantity)) {
        invalid();
        return;
    }
    ls.addLog(0, TotalCost);
}
void Run::runShowFinance(std::string command) {
    // std::cout << '?' << std::endl;
    if (nowAccount.Privilege < 7) {
        invalid();
        return;
    }
    if (command.length() == 12) {
        // std::cout << "!!\n";
        if (!ls.showFinance(-1)) {
            invalid();
        }
        return;
    }
    int p1 = 12;
    int p2 = getCount(command, p1 + 1);
    if (p2 != command.length()) {
        invalid();
        return;
    }
    if (p1 == command.length()) {
        invalid();
        return;
    }
    std::string count = command.substr(p1 + 1, p2 - p1 - 1);
    int number = getNumber(count);
    if (number < 0) {
        invalid();
        return;
    }
    if (!ls.showFinance(number)) {
        invalid();
        return;
    }
}