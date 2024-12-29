#include "Book.hpp"
#include "Account.hpp"
#include "Log.hpp"
#include "Command.hpp"
#include <iomanip>

/***********file storage test***********/

// BlockList<int, int> data;

// int hash(std::string &key) {
//     static constexpr int mod = 1e9 + 7;
//     static constexpr int base = 19260817;
//     int res = 0;
//     for (int i = 0; i < key.length(); ++i) {
//         res = (1ll * res * base % mod + key[i]) % mod; 
//     }
//     return res;
// }

// void insertInformation(std::string &key, int value) {
//     int val = hash(key);
//     data.insert(val, value);
// }
// void deleteInformation(std::string &key, int value) {
//     int val = hash(key);
//     data.mydelete(val, value);
// }
// void find(std::string &key) {
//     int val = hash(key);
//     std::vector<int> res = data.query(val);
//     if (res.empty()) {
//         std::cout << "null\n";
//     } else {
//         for (int x: res) {
//             std::cout << x << ' ';
//         }
//         std::cout << '\n';
//     }
// }

// int main() {
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);
//     std::cout.tie(nullptr);
//     data.initialize();
//     int T;
//     std::cin >> T;
//     while (T--) {
//         std::string opt, key;
//         int value;
//         std::cin >> opt;
//         if (opt[0] == 'i') {
//             std::cin >> key >> value;
//             insertInformation(key, value);
//         } else if (opt[0] == 'd') {
//             std::cin >> key >> value;
//             deleteInformation(key, value);
//         } else {
//             std::cin >> key;
//             find(key);
//         }
//     }
// }

/***********file storage test***********/

int main() {
    // freopen("testcase6.in", "r", stdin);
    // freopen("testcase6.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cout << std::fixed << std::setprecision(2);
    Run exe;
    exe.initialize();
    std::string str;
    while (true) {
        getline(std::cin, str);
        if (str == "quit" || str == "exit") {
            break;
        }
        else exe.run(str);
    }
}