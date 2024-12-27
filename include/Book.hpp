#ifndef BOOK_H
#define BOOK_H

#include <array>
#include <string>
#include "BlockList.hpp"

class String20 {
private:
    const static int maxLen = 20;
    int len;
    std::array<char, 20> str;
public:
    String20();
    String20(std::string);
    String20(std::array<char, 20>, int);
    int getLen();
    std::array<char, 20> getValue();
};

class String60 {
private:
    const static int maxLen = 60;
    int len;
    std::array<char, 60> str;
public:
    String60();
    String60(std::string);
    String60(std::array<char, 60>, int);
    int getLen();
    std::array<char, 60> getValue();
};

class Book {
private:
    String20 ISBN;
    String60 BookName, Author, Keyword;
    unsigned int number;
    double price;
};

class BookStorage {
private:
    BlockList<String20, Book> blockList1; // ISBN -> Book
    BlockList<String60, String20> blockList2; // BookName -> ISBN
    BlockList<String20, String20> blockList3; // Author -> ISBN
    BlockList<String20, String20> blockList4; // Keyword -> ISBN
};

#endif