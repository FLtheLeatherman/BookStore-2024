#include <algorithm>
#include <iomanip>
#include "BlockList.hpp"
#include "Book.hpp"

String20::String20() {
    len = 0;
}
String20::String20(std::string str) {
    len = str.length();
    for (int i = 0; i < len; ++i) {
        this->str[i] = str[i];
    }
}
String20::String20(std::array<char, 20> arr, size_t len) {
    this->len = len;
    for (int i = 0; i < len; ++i) {
        this->str[i] = arr[i];
    }
}
size_t String20::getLen() {
    return len;
}
std::array<char, 20> String20::getValue() {
    return str;
}
bool String20::operator <(const String20& RHS) {
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
bool String20::operator ==(const String20& RHS) {
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
String20 &String20::operator = (const String20 &RHS) {
    if (this == &RHS) {
        return (*this);
    }
    this->len = RHS.len;
    for (int i = 0; i < len; ++i) {
        this->str[i] = RHS.str[i];
    }
    return (*this);
}
std::ostream& operator <<(std::ostream &out, const String20 &str) {
    for (int i = 0; i < str.len; ++i) {
        out << str.str[i];
    }
    return out;
}

String60::String60() {
    len = 0;
}
String60::String60(std::string str) {
    len = str.length();
    for (int i = 0; i < len; ++i) {
        this->str[i] = str[i];
    }
}
String60::String60(std::array<char, 60> arr, size_t len) {
    this->len = len;
    for (int i = 0; i < len; ++i) {
        this->str[i] = arr[i];
    }
}
size_t String60::getLen() {
    return len;
}
std::array<char, 60> String60::getValue() {
    return str;
}
bool String60::operator <(const String60& RHS) {
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
bool String60::operator ==(const String60& RHS) {
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
String60 &String60::operator = (const String60 &RHS) {
    if (this == &RHS) {
        return (*this);
    }
    this->len = RHS.len;
    for (int i = 0; i < len; ++i) {
        this->str[i] = RHS.str[i];
    }
    return (*this);
}
std::ostream& operator <<(std::ostream &out, const String60 &str) {
    for (int i = 0; i < str.len; ++i) {
        out << str.str[i];
    }
    return out;
}

Book::Book() {
    id = 0;
    ISBN = String20();
    BookName = String60();
    Author = String60();
    Keyword = String60();
    number = 0;
    price = 0;
}
Book::Book(int id, String20 ISBN, String60 BookName, String60 Author, String60 Keyword, size_t number, double price) {
    this->id = id;
    this->ISBN = ISBN;
    this->BookName = BookName;
    this->Author = Author;
    this->Keyword = Keyword;
    this->number = number;
    this->price = price;
}
bool Book::operator <(const Book& RHS) {
    return this->ISBN < RHS.ISBN;
}
bool Book::operator ==(const Book& RHS) {
    return this->ISBN == RHS.ISBN;
}
std::ostream& operator <<(std::ostream &out, const Book& book) {
    out << book.ISBN;
    out << '\t';
    out << book.BookName;
    out << '\t';
    out << book.Author;
    out << '\t';
    out << book.Keyword;
    out << '\t';
    out << book.price;
    out << '\t';
    out << book.number;
    return out;
}

void BookStorage::initialize() {
    books.initialize("Books");
    blockList1.initialize("ISBN");
    blockList2.initialize("BookName");
    blockList3.initialize("Author");
    blockList4.initialize("Keyword");
    selected = false;
}
void BookStorage::show() {
    std::vector<Book> res = books.show();
    sort(res.begin(), res.end());
    if (!res.size()) {
        std::cout << '\n';
    } else {
        for (size_t i = 0; i < res.size(); ++i) {
            std::cout << res[i] << '\n';
        }
    }
}
void BookStorage::showISBN(String20 ISBN) {
    std::vector<int> res = blockList1.query(ISBN);
    if (res.empty()) {
        std::cout << '\n';
    } else {
        Book res2;
        books.read(res2, res[0]);
        std::cout << res2 << '\n';
    }
}
void BookStorage::showBookName(String60 BookName) {
    std::vector<int> res = blockList2.query(BookName);
    if (res.empty()) {
        std::cout << '\n';
    } else {
        std::vector<Book> res2;
        for (size_t i = 0; i < res.size(); ++i) {
            Book tmp;
            books.read(tmp, res[i]);
            res2.push_back(tmp);
        }
        sort(res2.begin(), res2.end());
        for (size_t i = 0; i < res.size(); ++i) {
            std::cout << res2[i] << '\n';
        }
    }
}
void BookStorage::showAuthor(String60 Author) {
    std::vector<int> res = blockList3.query(Author);
    if (res.empty()) {
        std::cout << '\n';
    } else {
        std::vector<Book> res2;
        for (size_t i = 0; i < res.size(); ++i) {
            Book tmp;
            books.read(tmp, res[i]);
            res2.push_back(tmp);
        }
        sort(res2.begin(), res2.end());
        for (size_t i = 0; i < res.size(); ++i) {
            std::cout << res2[i] << '\n';
        }
    }
}
bool BookStorage::showKeyword(String60 Keyword) {
    int len = Keyword.getLen();
    std::array<char, 60> str = Keyword.getValue();
    for (int i = 0; i < len; ++i) {
        if (str[i] == '|') {
            return false;
        }
    }
    std::vector<int> res = blockList4.query(Keyword);
    if (res.empty()) {
        std::cout << '\n';
    } else {
        std::vector<Book> res2;
        for (size_t i = 0; i < res.size(); ++i) {
            Book tmp;
            books.read(tmp, res[i]);
            res2.push_back(tmp);
        }
        sort(res2.begin(), res2.end());
        for (size_t i = 0; i < res.size(); ++i) {
            std::cout << res2[i] << '\n';
        }
    }
    return true;
}
double BookStorage::buy(String20 ISBN, size_t quantity) {
    std::vector<int> res = blockList1.query(ISBN);
    if (!res.size()) {
        return -1;
    } else {
        Book now;
        books.read(now, res[0]);
        if (now.number < quantity || quantity == 0) {
            return -1;
        }
        std::cout << std::fixed << std::setprecision(2) << now.price * quantity << '\n';
        now.number -= quantity;
        books.write(now, res[0]);
        return now.price * quantity;
    }
}
void BookStorage::select(int id) {
    if (id == -1) {
        selected = false;
    } else {
        selected = true;
    }
    current = id;
}
int BookStorage::select(String20 ISBN) {
    if (!ISBN.getLen()) {
        return -1;
    }
    std::vector<int> res = blockList1.query(ISBN);
    if (!res.size()) {
        Book tmp;
        books.get_info(tmp.id, 1);
        tmp.id++;
        books.write_info(tmp.id, 1);
        tmp.ISBN = ISBN;
        blockList1.insert(ISBN, tmp.id);
        blockList2.insert(String60(), tmp.id);
        blockList3.insert(String60(), tmp.id);
        blockList4.insert(String60(), tmp.id);
        res.push_back(tmp.id);
        books.write(tmp, tmp.id);
    }
    selected = true;
    current = res[0];
    return current;
}
bool BookStorage::modifyISBN(String20 ISBN) {
    if (!selected) {
        return false;
    }
    Book now;
    books.read(now, current);
    if (ISBN == now.ISBN) {
        return false;
    }
    std::vector<int> tmp = blockList1.query(ISBN);
    if (tmp.size()) {
        return false;
    }
    blockList1.mydelete(now.ISBN, current);
    now.ISBN = ISBN;
    blockList1.insert(now.ISBN, current);
    books.write(now, current);
    return true;
}
bool BookStorage::modifyBookName(String60 BookName) {
    if (!selected) {
        return false;
    }
    Book now;
    books.read(now, current);
    blockList2.mydelete(now.BookName, current);
    now.BookName = BookName;
    blockList2.insert(now.BookName, current);
    books.write(now, current);
    return true;
}
bool BookStorage::modifyAuthor(String60 Author) {
    if (!selected) {
        return false;
    }
    Book now;
    books.read(now, current);
    blockList3.mydelete(now.Author, current);
    now.Author = Author;
    blockList3.insert(now.Author, current);
    books.write(now, current);
    return true;
}
bool BookStorage::modifyKeyword(String60 Keyword) {
    if (!selected) {
        return false;
    }
    Book now;
    books.read(now, current);
    int len = now.Keyword.getLen();
    std::array<char, 60> keyword = now.Keyword.getValue();
    std::string tmp = "";
    for (int i = 0; i < len; ++i) {
        if (keyword[i] == '|') {
            blockList4.mydelete(String60(tmp), current);
            tmp = "";
        } else {
            tmp += keyword[i];
        }
    }
    blockList4.mydelete(String60(tmp), current);
    tmp = "";
    now.Keyword = Keyword;
    len = now.Keyword.getLen();
    keyword = now.Keyword.getValue();
    for (int i = 0; i < len; ++i) {
        if (keyword[i] == '|') {
            blockList4.insert(String60(tmp), current);
            tmp = "";
        } else {
            tmp += keyword[i];
        }
    }
    blockList4.insert(String60(tmp), current);
    books.write(now, current);
    return true;
}
bool BookStorage::modifyPrice(double price) {
    if (!selected) {
        return false;
    }
    Book now;
    books.read(now, current);
    now.price = price;
    books.write(now, current);
    return true;
}
bool BookStorage::import(size_t quantity) {
    if (!selected) {
        return false;
    }
    Book now;
    books.read(now, current);
    now.number += quantity;
    books.write(now, current);
    return true;
}