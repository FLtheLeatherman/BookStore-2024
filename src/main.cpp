#include "Book.hpp"
#include "Account.hpp"
#include "Log.hpp"
#include "Command.hpp"
#include <iomanip>

std::string command;
bool read() {
    command = "";
    char ch;
    while (std::cin.get(ch)) {
        if (ch == '\r' || ch == '\n') {
            return true;
        }
        command += ch;
    }
    return false;
}

void format(std::string &str) {
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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cout << std::fixed << std::setprecision(2);
    Run main;
    main.initialize();
    while (true) {
        bool flag = read();
        if (!command.size()) {
            if (!flag) {
                break;
            }
            continue;
        }
        format(command);
        if (command == "quit" || command == "exit") {
            break;
        }
        else main.run(command);
        if (!flag) {
            break;
        }
    }
}