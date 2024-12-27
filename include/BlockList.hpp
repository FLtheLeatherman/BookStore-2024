#ifndef BLOCKLIST_H
#define BLOCKLIST_H

// 需要进行修改以使其更加美观。

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

// 应当保证: T1, T2 可以被排序且可以被输出
// T1, T2 的大小应固定; 字符串类使用 std::array 实现.
// #define T1 int
// #define T2 int
template<typename T1, typename T2>
class BlockList {
public:
    struct node1 {
        int nxtAddr;
        int sizAddr;
        int nxtLevelAddr;
        T1 headKey;
        T2 headValue;
        node1(int nxtAddr = -1, int sizAddr = -1, int nxtLevelAddr = -1, T1 headKey = 0, T2 headValue = 0) {
            this->nxtAddr = nxtAddr;
            this->sizAddr = sizAddr;
            this->nxtLevelAddr = nxtLevelAddr;
            this->headKey = headKey;
            this->headValue = headValue;
        }
        std::pair<T1, T2> getValue() {
            return std::make_pair(headKey, headValue);
        }
    };
    struct node2 {
        int nxtAddr;
        T1 key;
        T2 value;
        node2(int nxtAddr = -1, T1 key = 0, T2 value = 0) {
            this->nxtAddr = nxtAddr;
            this->key = key;
            this->value = value;
        }
        std::pair<T1, T2> getValue() {
            return std::make_pair(key, value);
        }
    };
    struct fileReader {
        std::string fileName;
        std::fstream file;
        fileReader() = default;
        void initialize(std::string str = "") {
            fileName = str;
            file.open(fileName, std::ios::in | std::ios::out | std::ios::binary);
            if (!file) {
                file.open(fileName, std::ios::out);
            }
            file.close();
            file.open(fileName, std::ios::in | std::ios::out | std::ios::binary);
        }
        void read(int &value, int addr) {
            int size = sizeof(int);
            file.seekp(addr);
            file.read(reinterpret_cast<char*>(&value), size);
        }
        void read(node1 &value, int addr) {
            int size = sizeof(node1);
            file.seekp(addr);
            file.read(reinterpret_cast<char*>(&value), size);
        }
        void read(node2 &value, int addr) {
            int size = sizeof(node2);
            file.seekp(addr);
            file.read(reinterpret_cast<char*>(&value), size);
        }
        void write(int &value, int addr) {
            int size = sizeof(int);
            file.seekg(addr);
            file.write(reinterpret_cast<char*>(&value), size);
        }
        void write(node1 &value, int addr) {
            int size = sizeof(node1);
            file.seekg(addr);
            file.write(reinterpret_cast<char*>(&value), size);
        }
        void write(node2 &value, int addr) {
            int size = sizeof(node2);
            file.seekg(addr);
            file.write(reinterpret_cast<char*>(&value), size);
        }
        int getEnd() {
            file.seekp(0, std::ios::end);
            int res = file.tellp();
            return res;
        }
        void close() {
            file.close();
        }
    };
    class blocks {
    private:
        const static int sizeLimit = 20;
    public:
        fileReader head, body;
        std::string filePreffix;
        int len;
        std::vector<int> headAddr;
        std::vector<node1> heads;
        void initialize(std::string str = "") {
            filePreffix = str;
            head.initialize(filePreffix + "_head");
            head.read(len, 0);
            for (int i = 0; i < len; ++i) {
                int tmp;
                head.read(tmp, (i + 1) * sizeof(int));
                headAddr.push_back(tmp);
            }
            head.close();
            body.initialize(filePreffix + "_body");
            for (int i = 0; i < len; ++i) {
                node1 tmp;
                body.read(tmp, headAddr[i]);
                heads.push_back(tmp);
            }
        }
        void insert(T1 key, T2 value) {
            if (!len) {
                int addr2 = body.getEnd();
                node2 tmp2(-1, key, value);
                body.write(tmp2, addr2);
                int siz = 1;
                int sizAddr = body.getEnd();
                body.write(siz, sizAddr);
                int addr1 = body.getEnd();
                node1 tmp1(-1, sizAddr, addr2, key, value);
                body.write(tmp1, addr1);
                len = 1;
                headAddr.push_back(addr1);
                heads.push_back(tmp1);
            } else {
                std::pair<T1, T2> now = std::make_pair(key, value);
                int pos = headAddr.size() - 1;
                for (size_t i = 0; i < headAddr.size(); ++i) {
                    if (heads[i].getValue() > now) {
                        pos = i - 1;
                        break;
                    }
                }
                int hdAddr = headAddr[0];
                node1 tmp1;
                if (pos == -1) {
                    pos = 0;
                    tmp1 = heads[pos];
                    node2 tmp2(tmp1.nxtLevelAddr, key, value);
                    tmp1.nxtLevelAddr = body.getEnd();
                    int size;
                    body.read(size, tmp1.sizAddr);
                    size++;
                    body.write(size, tmp1.sizAddr);
                    tmp1.headKey = key, tmp1.headValue = value;
                    body.write(tmp2, tmp1.nxtLevelAddr);
                    body.write(tmp1, hdAddr);
                    heads[0] = tmp1;
                } else {
                    hdAddr = headAddr[pos];
                    tmp1 = heads[pos];
                    node2 cur, nxt;
                    body.read(cur, tmp1.nxtLevelAddr);
                    int curAddr = tmp1.nxtLevelAddr;
                    while (true) {
                        if (cur.nxtAddr == -1) {
                            break;
                        }
                        body.read(nxt, cur.nxtAddr);
                        if (nxt.getValue() > now) {
                            break;
                        }
                        curAddr = cur.nxtAddr;
                        cur = nxt;
                    }
                    if (cur.getValue() != now) {
                        int size;
                        body.read(size, tmp1.sizAddr);
                        size++;
                        body.write(size, tmp1.sizAddr);
                        if (cur.nxtAddr == -1) {
                            cur.nxtAddr = body.getEnd();
                            node2 tmp2(-1, key, value);
                            body.write(tmp2, cur.nxtAddr);
                            body.write(cur, curAddr);
                        } else {
                            node2 tmp2(cur.nxtAddr, key, value);
                            cur.nxtAddr = body.getEnd();
                            body.write(tmp2, cur.nxtAddr);
                            body.write(cur, curAddr);
                        }
                    }
                }
                int size;
                body.read(size, tmp1.sizAddr);
                if (size > sizeLimit * 2) {
                    int size2 = size - sizeLimit;
                    size = sizeLimit;
                    body.write(size, tmp1.sizAddr);
                    int cnt = size;
                    int cur = tmp1.nxtLevelAddr;
                    for (int i = 0; i < cnt; ++i) {
                        node2 sb;
                        body.read(sb, cur);
                        if (i == cnt - 1) {
                            int ps = cur;
                            cur = sb.nxtAddr;
                            sb.nxtAddr = -1;
                            body.write(sb, ps);
                        } else {
                            cur = sb.nxtAddr;
                        }
                    }
                    int newSizAddr = body.getEnd();
                    body.write(size2, newSizAddr);
                    node2 sb;
                    body.read(sb, cur);
                    node1 newNode(tmp1.nxtAddr, newSizAddr, cur, sb.key, sb.value);
                    int newAddr = body.getEnd();
                    body.write(newNode, newAddr);
                    tmp1.nxtAddr = newAddr;
                    body.write(tmp1, hdAddr);
                    heads[pos] = tmp1;
                    len++;
                    headAddr.insert(headAddr.begin() + pos + 1, newAddr);
                    heads.insert(heads.begin() + pos + 1, newNode);
                }
            }
        }
        void mydelete(T1 key, T2 value) {
            std::pair<T1, T2> now = std::make_pair(key, value);
            int pos = len - 1;
            if (pos < 0) {
                return;
            }
            for (size_t i = 0; i < len; ++i) {
                node1 tmp = heads[i];
                if (tmp.getValue() > now) {
                    pos = i - 1;
                    break;
                }
            }
            pos = std::max(0, pos);
            int hdAddr = headAddr[pos];
            node1 tmp1 = heads[pos];
            int size;
            body.read(size, tmp1.sizAddr);
            if (tmp1.getValue() == now) {
                node2 tmp2;
                body.read(tmp2, tmp1.nxtLevelAddr);
                tmp1.nxtLevelAddr = tmp2.nxtAddr;
                if (tmp2.nxtAddr != -1) {
                    body.read(tmp2, tmp2.nxtAddr);
                    tmp1.headKey = tmp2.key, tmp1.headValue = tmp2.value;
                }
                size--;
                body.write(size, tmp1.sizAddr);
                body.write(tmp1, hdAddr);
                heads[pos] = tmp1;
            } else {
                node2 lst, cur;
                body.read(lst, tmp1.nxtLevelAddr);
                body.read(cur, lst.nxtAddr);
                int lstAddr = tmp1.nxtLevelAddr;
                while (true) {
                    if (cur.nxtAddr == -1) {
                        break;
                    }
                    if (cur.getValue() >= now) {
                        break;
                    }
                    lstAddr = lst.nxtAddr;
                    lst = cur;
                    body.read(cur, cur.nxtAddr);
                }
                if (cur.getValue() == now) {
                    lst.nxtAddr = cur.nxtAddr;
                    body.write(lst, lstAddr);
                    size--;
                    body.write(size, tmp1.sizAddr);
                }
            }
            if (!size) {
                if (pos > 0) {
                    node1 tmp;
                    body.read(tmp, headAddr[pos - 1]);
                    tmp.nxtAddr = tmp1.nxtAddr;
                    body.write(tmp, headAddr[pos - 1]);
                    heads[pos - 1] = tmp;
                }
                len--;
                headAddr.erase(headAddr.begin() + pos);
                heads.erase(heads.begin() + pos);
            }
        }
        bool query(T1 key, int pos) {
            node1 tmp = heads[pos];
            node2 cur;
            body.read(cur, tmp.nxtLevelAddr);
            bool flag = false;
            while (true) {
                if (cur.key == key) {
                    flag = true;
                    std::cout << cur.value << ' ';
                }
                if (cur.key > key) {
                    break;
                }
                if (cur.nxtAddr == -1) {
                    break;
                }
                body.read(cur, cur.nxtAddr);
            }
            return flag;
        }
        void query(T1 key) {
            std::pair<T1, int> now = std::make_pair(key, -1);
            int pos = headAddr.size() - 1;
            for (size_t i = 0; i < headAddr.size(); ++i) {
                node1 tmp = heads[i];
                if (tmp.headKey >= key) {
                    pos = i;
                    break;
                }
            }
            if (pos == -1) {
                std::cout << "null";
            } else {
                bool flag = true;
                bool flag2 = false;
                if (pos > 0) {
                    flag2 |= query(key, pos - 1);
                }                
                for (size_t i = pos; i < headAddr.size(); ++i) {
                    if (heads[i].headKey > key) {
                        break;
                    }
                    bool res = query(key, i);
                    flag &= res;
                    flag2 |= res;
                    if (!flag) break;
                }
                if (!flag2) {
                    std::cout << "null";
                }
            }
            std::cout << '\n';
        }
    };
    blocks sb;
    void initialize(std::string str = "") {
        sb.initialize(str);
    }
    void insert(T1 key, T2 value) {
        sb.insert(key, value);
    }
    void mydelete(T1 key, T2 value) {
        sb.mydelete(key, value);
    }
    void query(T1 key) {
        sb.query(key);
    }
    ~BlockList() {
        sb.body.close();
        sb.head.initialize(sb.filePreffix + "_head");
        sb.head.write(sb.len, 0);
        for (int i = 0; i < sb.len; ++i) {
            sb.head.write(sb.headAddr[i], (i + 1) * sizeof(int));
        }
        sb.headAddr.clear();
        sb.head.close();
    }
};

#endif