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
    ISBN = String20();
    BookName = String60();
    Author = String60();
    Keyword = String60();
    number = 0;
    price = 0;
}
Book::Book(String20 ISBN, String60 BookName, String60 Author, String60 Keyword, size_t number, double price) {
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
    blockList1.initialize("ISBN");
    // std::cout << "GOOD1" << std::endl;
    blockList2.initialize("BookName");
    // std::cout << "GOOD2" << std::endl;
    blockList3.initialize("Author");
    // std::cout << "GOOD3" << std::endl;
    blockList4.initialize("Keyword");
    // std::cout << "GOOD4" << std::endl;
    selected = false;
}
void BookStorage::show() {
    std::vector<Book> res = blockList1.show();
    if (res.empty()) {
        std::cout << '\n';
    } else {
        for (Book b: res) {
            std::cout << b << '\n';
        }
    }
}
void BookStorage::showISBN(String20 ISBN) {
    std::vector<Book> res = blockList1.query(ISBN);
    if (res.empty()) {
        std::cout << '\n';
    } else {
        std::cout << res[0] << '\n';
    }
}
void BookStorage::showBookName(String60 BookName) {
    std::vector<String20> res = blockList2.query(BookName);
    std::sort(res.begin(), res.end());
    if (res.empty()) {
        std::cout << '\n';
    } else {
        for (String20 ISBN: res) {
            showISBN(ISBN);
        }
    }
}
void BookStorage::showAuthor(String60 Author) {
    std::vector<String20> res = blockList3.query(Author);
    std::sort(res.begin(), res.end());
    if (res.empty()) {
        std::cout << '\n';
    } else {
        for (String20 ISBN: res) {
            showISBN(ISBN);
        }
    }
}
bool BookStorage::showKeyword(String60 Keyword) {
    int len = Keyword.getLen();
    std::array<char, 60> str = Keyword.getValue();
    for (size_t i = 0; i < len; ++i) {
        if (str[i] == '|') {
            return false;
        }
    }
    std::vector<String20> res = blockList4.query(Keyword);
    std::sort(res.begin(), res.end());
    if (res.empty()) {
        std::cout << '\n';
    } else {
        for (String20 ISBN: res) {
            showISBN(ISBN);
        }
    }
    return true;
}
double BookStorage::buy(String20 ISBN, size_t quantity) {
    std::vector<Book> res = blockList1.query(ISBN);
    if (!res.size()) {
        return -1;
    } else {
        if (res[0].number < quantity || quantity == 0) {
            return -1;
        }
        std::cout << std::fixed << std::setprecision(2) << res[0].price * quantity << '\n';
        blockList1.mydelete(ISBN, res[0]);
        res[0].number -= quantity;
        blockList1.insert(ISBN, res[0]);
        return res[0].price * quantity;
    }
}
Book BookStorage::select(String20 ISBN) {
    if (!ISBN.getLen()) {
        selected = false;
        current = Book();
        return current;
    }
    std::vector<Book> res = blockList1.query(ISBN);
    if (!res.size()) {
        Book tmp;
        tmp.ISBN = ISBN;
        blockList1.insert(ISBN, tmp);
        blockList2.insert(String60(), ISBN);
        blockList3.insert(String60(), ISBN);
        blockList4.insert(String60(), ISBN);
        res.push_back(tmp);
    }
    selected = true;
    current = res[0];
    return current;
}
bool BookStorage::modifyISBN(String20 ISBN) {
    if (!selected) {
        return false;
    }
    // std::cout << ISBN << ' ' << current.ISBN << std::endl;
    if (ISBN == current.ISBN) {
        return false;
    }
    std::vector<Book> res = blockList1.query(ISBN);
    if (!res.empty()) {
        return false;
    }
    blockList1.mydelete(current.ISBN, current);
    blockList2.mydelete(current.BookName, current.ISBN);
    blockList3.mydelete(current.Author, current.ISBN);
    int len = current.Keyword.getLen();
    std::array<char, 60> Keyword = current.Keyword.getValue();
    std::string tmp = "";
    for (int i = 0; i < len; ++i) {
        if (Keyword[i] == '|') {
            blockList4.mydelete(String60(tmp), current.ISBN);
            tmp = "";
        } else {
            tmp += Keyword[i];
        }
    }
    blockList4.mydelete(String60(tmp), current.ISBN);
    tmp = "";
    current.ISBN = ISBN;
    blockList1.insert(current.ISBN, current);
    blockList2.insert(current.BookName, current.ISBN);
    blockList3.insert(current.Author, current.ISBN);
    for (int i = 0; i < len; ++i) {
        if (Keyword[i] == '|') {
            blockList4.insert(String60(tmp), current.ISBN);
            tmp = "";
        } else {
            tmp += Keyword[i];
        }
    }
    blockList4.insert(String60(tmp), current.ISBN);
    tmp = "";
    return true;
}
bool BookStorage::modifyBookName(String60 BookName) {
    if (!selected) {
        return false;
    }
    blockList1.mydelete(current.ISBN, current);
    blockList2.mydelete(current.BookName, current.ISBN);
    current.BookName = BookName;
    blockList1.insert(current.ISBN, current);
    blockList2.insert(current.BookName, current.ISBN);
    return true;
}
bool BookStorage::modifyAuthor(String60 Author) {
    if (!selected) {
        return false;
    }
    blockList1.mydelete(current.ISBN, current);
    blockList3.mydelete(current.Author, current.ISBN);
    current.Author = Author;
    blockList1.insert(current.ISBN, current);
    blockList3.insert(current.Author, current.ISBN);
    return true;
}
bool BookStorage::modifyKeyword(String60 Keyword) {
    if (!selected) {
        return false;
    }
    blockList1.mydelete(current.ISBN, current);
    int len = current.Keyword.getLen();
    std::array<char, 60> keyword = current.Keyword.getValue();
    std::string tmp = "";
    for (int i = 0; i < len; ++i) {
        if (keyword[i] == '|') {
            blockList4.mydelete(String60(tmp), current.ISBN);
            tmp = "";
        } else {
            tmp += keyword[i];
        }
    }
    blockList4.mydelete(String60(tmp), current.ISBN);
    tmp = "";
    current.Keyword = Keyword;
    blockList1.insert(current.ISBN, current);
    len = current.Keyword.getLen();
    keyword = current.Keyword.getValue();
    for (int i = 0; i < len; ++i) {
        if (keyword[i] == '|') {
            blockList4.insert(String60(tmp), current.ISBN);
            tmp = "";
        } else {
            tmp += keyword[i];
        }
    }
    blockList4.insert(String60(tmp), current.ISBN);
    return true;
}
bool BookStorage::modifyPrice(double price) {
    if (!selected) {
        return false;
    }
    blockList1.mydelete(current.ISBN, current);
    current.price = price;
    blockList1.insert(current.ISBN, current);
    return true;
}
bool BookStorage::import(size_t quantity) {
    if (!selected) {
        return false;
    }
    blockList1.mydelete(current.ISBN, current);
    current.number += quantity;
    blockList1.insert(current.ISBN, current);
    return true;
}