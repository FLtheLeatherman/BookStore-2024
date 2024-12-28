#ifndef BPT_MEMORYRIVER_HPP
#define BPT_MEMORYRIVER_HPP

#include <fstream>

using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

// struct node {
//     node *nxt;
//     int addr;
//     node() {
//         nxt = nullptr;
//     }
// };
template<typename T, int info_len = 2>
class MemoryRiver {
private:
    /* your code here */
    // node *head = nullptr;
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
        }
        file.close();
        file.open(file_name, std::ios::in | std::ios::out | std::ios::binary);
    }

    //读出第n个int的值赋给tmp，1_base
    void get_info(int &tmp, int n) {
        if (n > info_len) return;
        /* your code here */
        // file.open(file_name, std::ios::in);
        file.seekg((n - 1) * sizeof(int));
        file.read(reinterpret_cast<char*>(&tmp), sizeof(int));
        // file.close();
    }

    //将tmp写入第n个int的位置，1_base
    void write_info(int tmp, int n) {
        if (n > info_len) return;
        /* your code here */
        // file.open(file_name, std::ios::in | std::ios::out);
        file.seekp((n - 1) * sizeof(int));
        file.write(reinterpret_cast<char*>(&tmp), sizeof(int));
        // file.close();
    }

    //在文件合适位置写入类对象t，并返回写入的位置索引index
    //位置索引意味着当输入正确的位置索引index，在以下三个函数中都能顺利的找到目标对象进行操作
    //位置索引index可以取为对象写入的起始位置
    // int write(T &t) {
    //     /* your code here */
    //     file.open(file_name, std::ios::in | std::ios::out);
    //     if (head == nullptr) {
    //         // std::cerr << "Yes?" << std::endl;
    //         file.seekp(0, std::ios::end);
    //     } else {
    //         file.seekp(head->addr, std::ios::beg);
    //         node *p = new node;
    //         p = head;
    //         head = head->nxt;
    //         delete p;
    //     }
    //     int index = file.tellp();
    //     file.write(reinterpret_cast<char*>(&t), sizeofT);
    //     file.close();
    //     return index;
    // }

    //用t的值更新位置索引index对应的对象，保证调用的index都是由write函数产生
    // void update(T &t, const int index) {
    //     /* your code here */
    //     file.open(file_name, std::ios::in | std::ios::out);
    //     file.seekg(index);
    //     file.write(reinterpret_cast<char*>(&t), sizeofT);
    //     file.close();
    // }

    //读出位置索引index对应的T对象的值并赋值给t，保证调用的index都是由write函数产生
    // void read(T &t, const int index) {
    //     /* your code here */
    //     file.open(file_name, std::ios::in);
    //     file.seekp(index);
    //     file.read(reinterpret_cast<char*>(&t), sizeofT);
    //     file.close();
    // }

    //删除位置索引index对应的对象(不涉及空间回收时，可忽略此函数)，保证调用的index都是由write函数产生
    // void Delete(int index) {
    //     /* your code here */
    //     node *p = new node;
    //     p->addr = index;
    //     if (head != nullptr) {
    //         p->nxt = head->nxt;
    //         head = p;
    //     } else {
    //         head = p;
    //         head->nxt = nullptr;
    //     }
    // }

    void read(T &t, int index) {
        file.seekp(info_len * sizeof(int) + (index - 1) * sizeofT);
        file.read(reinterpret_cast<char*>(&t), sizeofT);
    }

    void write(T &t, int index) {
        file.seekp(info_len * sizeof(int) + (index - 1) * sizeofT);
        file.write(reinterpret_cast<char*>(&t), sizeofT);
    }

    ~MemoryRiver() {
        file.close();
    }

};
#endif //BPT_MEMORYRIVER_HPP