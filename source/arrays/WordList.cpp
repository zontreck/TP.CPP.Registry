#include "WordList.h"
#include <iostream>

WordList::WordList(const std::string& name) : Entry(name) {
    Type = EntryType::WordArray;
    Description = "";
}

void WordList::ReadValue(std::ifstream& stream) {
    int count;
    stream.read(reinterpret_cast<char*>(&count), sizeof(count));

    for (int i = 0; i < count; i++) {
        std::string item;
        std::getline(stream, item, '\0');
        value.push_back(item);
    }
}

void WordList::Write(std::ofstream& stream) {
    int count = static_cast<int>(value.size());
    stream.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (const std::string& item : value) {
        stream.write(item.c_str(), item.size() + 1);
    }
}

std::string WordList::PrettyPrint(int indent) {
    std::string str = Entry::PrettyPrint(indent);
    std::string ind = std::string(indent + 4, ' ');

    str += " [" + std::to_string(value.size()) + "]\n";
    str += ind + "{\n";
    for (const std::string& item : value) {
        str += ind + "\"" + item + "\",\n";
    }
    if (!value.empty()) {
        str.pop_back();  // Remove the trailing comma.
    }
    str += "\n" + ind + "}";
    return str;
}

int WordList::indexOf(const std::string& item) const {
    auto it = std::find(value.begin(), value.end(), item);
    if (it != value.end()) {
        return std::distance(value.begin(), it);
    }
    return -1;
}

void WordList::insert(int index, const std::string& item) {
    if (index >= 0 && index <= static_cast<int>(value.size())) {
        value.insert(value.begin() + index, item);
    }
}

void WordList::removeAt(int index) {
    if (index >= 0 && index < static_cast<int>(value.size())) {
        value.erase(value.begin() + index);
    }
}

void WordList::add(const std::string& item) {
    value.push_back(item);
}

void WordList::clear() {
    value.clear();
}

bool WordList::contains(const std::string& item) const {
    return std::find(value.begin(), value.end(), item) != value.end();
}

std::vector<std::string>::iterator WordList::begin() {
    return value.begin();
}

std::vector<std::string>::iterator WordList::end() {
    return value.end();
}
