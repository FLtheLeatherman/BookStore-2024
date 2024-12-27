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
String20::String20(std::array<char, 20> arr, int len) {
    this->len = len;
    for (int i = 0; i < len; ++i) {
        this->str[i] = arr[i];
    }
}
int String20::getLen() {
    return len;
}
std::array<char, 20> String20::getValue() {
    return str;
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
String60::String60(std::array<char, 60> arr, int len) {
    this->len = len;
    for (int i = 0; i < len; ++i) {
        this->str[i] = arr[i];
    }
}
int String60::getLen() {
    return len;
}
std::array<char, 60> String60::getValue() {
    return str;
}