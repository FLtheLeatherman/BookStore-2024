#ifndef BOOK_H
#define BOOK_H

#include <array>
#include <string>
#include <iostream>
#include "BlockList.hpp"
#include "MemoryRiver.hpp"

class String20 {
private:
    size_t len;
    std::array<char, 20> str;
public:
    String20();
    String20(std::string);
    String20(std::array<char, 20>, size_t);
    size_t getLen();
    std::array<char, 20> getValue();
    bool operator <(const String20 &);
    bool operator ==(const String20 &);
    String20 &operator = (const String20 &);
    friend std::ostream& operator <<(std::ostream &, const String20 &);
};

class String60 {
private:
    size_t len;
    std::array<char, 60> str;
public:
    String60();
    String60(std::string);
    String60(std::array<char, 60>, size_t);
    size_t getLen();
    std::array<char, 60> getValue();
    bool operator <(const String60 &);
    bool operator ==(const String60 &);
    String60 &operator = (const String60 &);
    friend std::ostream& operator <<(std::ostream &, const String60 &);
};

class Book {
public:
    int id;
    String20 ISBN;
    String60 BookName, Author, Keyword;
    size_t number;
    double price;
    Book();
    Book(int id, String20 ISBN, String60 BookName, String60 Author, String60 Keyword, size_t number, double price);
    bool operator <(const Book &);
    bool operator ==(const Book &);
    friend std::ostream& operator <<(std::ostream &, const Book &);
};

class BookStorage {
private:
    MemoryRiver<Book, 1> books; // id -> Book
    BlockList<String20, int> blockList1; // ISBN -> id
    BlockList<String60, int> blockList2; // BookName -> id
    BlockList<String60, int> blockList3; // Author -> id
    BlockList<String60, int> blockList4; // Keyword -> id
    bool selected;
    int current;
public:
    void initialize();
    ~BookStorage() = default;
    void show();
    void showISBN(String20 ISBN);
    void showBookName(String60 BookName);
    void showAuthor(String60 Author);
    bool showKeyword(String60 Keyword);
    double buy(String20 ISBN, size_t quantity);
    void select(int id);
    int select(String20 ISBN);
    bool modifyISBN(String20 ISBN);
    bool modifyBookName(String60 BookName);
    bool modifyAuthor(String60 Author);
    bool modifyKeyword(String60 Keyword);
    bool modifyPrice(double price);
    bool import(size_t quantity);
};

#endif