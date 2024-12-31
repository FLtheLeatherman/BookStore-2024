#ifndef BPT_MEMORYRIVER_HPP
#define BPT_MEMORYRIVER_HPP

#include <fstream>
#include <vector>
#include <iostream>

using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

template<typename T, int info_len = 2>
class MemoryRiver {
private:
    fstream file;
    string file_name;
    int sizeofT = sizeof(T);
public:
    MemoryRiver() = default;

    MemoryRiver(const string& file_name) : file_name(file_name) {}

    void initialize(string FN = "") {
        sizeofT = sizeof(T);
        file_name = FN;
        file.open(file_name, std::ios::in | std::ios::out | std::ios::binary);
        if (!file) {
            file.open(file_name, std::ios::out);
            file.seekp(0);
            int tmp = 0;
            file.write(reinterpret_cast<char*>(&tmp), sizeof(int));
        }
        file.close();
        file.open(file_name, std::ios::in | std::ios::out | std::ios::binary);
    }

    void get_info(int &tmp, int n) {
        if (n > info_len) return;
        file.seekg((n - 1) * sizeof(int));
        file.read(reinterpret_cast<char*>(&tmp), sizeof(int));
    }

    void write_info(int tmp, int n) {
        if (n > info_len) return;
        file.seekp((n - 1) * sizeof(int));
        file.write(reinterpret_cast<char*>(&tmp), sizeof(int));
    }

    void read(T &t, int index) {
        file.seekg(info_len * sizeof(int) + (index - 1) * sizeofT);
        file.read(reinterpret_cast<char*>(&t), sizeofT);
    }

    void write(T &t, int index) {
        file.seekp(info_len * sizeof(int) + (index - 1) * sizeofT);
        file.write(reinterpret_cast<char*>(&t), sizeofT);
    }

    std::vector<T> show() {
        int len;
        get_info(len, 1);
        std::vector<T> res(len);
        for (int i = 0; i < len; ++i) {
            read(res[i], i + 1);
        }
        return res;
    }

    ~MemoryRiver() {
        file.close();
    }

};
#endif //BPT_MEMORYRIVER_HPP