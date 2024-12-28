#include <string>
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

void Run::run(std::string command) {
    if (command.substr(0, 3) == "su ") {
        runRegister(command);
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
    } else if (command.substr(0, 5) == "show ") {
        runShow(command);
    } else if (command.substr(0, 4) == "buy ") {
        runBuy(command);
    } else if (command.substr(0, 7) == "select ") {
        runSelect(command);
    } else if (command.substr(0, 7) == "modify ") {
        runModify(command);
    } else if (command.substr(0, 7) == "import ") {
        runImport(command);
    } else if (command.substr(0, 13) == "show finance ") {
        runShow(command);
    } else {
        invalid();
    }
}

int Run::getUserID(std::string str, int pos) {
    for (int i = pos; i < str.length(); ++i) {
        if (isdigit(str[i]) || isalpha(str[i]) || (str[i] == '_')
        ) {
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
        if (isprint(str[i])) {
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
        if (isdigit(str[i])) {
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
        if (isprint(str[i])) {
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
        if (isprint(str[i]) && str[i] == '\"') {
            continue;
        }
        if (str[i] == ' ') {
            if (i - pos > 60) return -1;
            return i;
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

void Run::runSu(std::string command) {
    int p1 = 3;
    int p2 = getUserID(command, p1);
    if (p2 == -1) {
        invalid();
    }
    if (p2 == command.length()) {
        String30 UserID = command.substr(p1, p2 - p1), Password;
        if (!as.login(UserID, Password)) {
            invalid();
        }
    } else {
        int p3 = getPassword(command, p2 + 1);
        if (p3 == -1) {
            invalid();
        }
        String30 UserID = command.substr(p1, p2 - p1), Password = command.substr(p2 + 1, p3 - p2 - 1);
        if (!as.login(UserID, Password)) {
            invalid();
        }
    }
}
void Run::runLogout(std::string) {

}
void Run::runRegister(std::string) {

}
void Run::runPasswd(std::string) {

}
void Run::runUseradd(std::string) {

}
void Run::runDelete(std::string) {

}
void Run::runShow(std::string) {

}
void Run::runBuy(std::string) {

}
void Run::runSelect(std::string) {

}
void Run::runModify(std::string) {

}
void Run::runImport(std::string) {

}
void Run::runShowFinance(std::string) {

}