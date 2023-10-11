#include "ByteList.h"

ByteList::ByteList(const std::string& name) : Entry(name) {
    Type = EntryType::ByteArray;
    Description = "";
}

void ByteList::ReadValue(std::ifstream& stream) {
    int count;
    stream.read(reinterpret_cast<char*>(&count), sizeof(count));

    for (int i = 0; i < count; i++) {
        unsigned char item;
        stream.read(reinterpret_cast<char*>(&item), sizeof(item));
        value.push_back(item);
    }
}

void ByteList::Write(std::ofstream& stream) {
    int count = static_cast<int>(value.size());
    stream.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (unsigned char item : value) {
        stream.write(reinterpret_cast<const char*>(&item), sizeof(item));
    }
}

std::string ByteList::PrettyPrint(int indent) {
    std::string str = Entry::PrettyPrint(indent);
    std::string ind = std::string(indent + 4, ' ');

    str += " [" + std::to_string(value.size()) + "]\n";
    str += ind + "{\n";
    for (unsigned char item : value) {
        str += ind + std::to_string(static_cast<int>(item)) + ",\n";
    }
    if (!value.empty()) {
        str.pop_back();  // Remove the trailing comma.
    }
    str += "\n" + ind + "}";
    return str;
}

int ByteList::indexOf(unsigned char item) const {
    auto it = std::find(value.begin(), value.end(), item);
    if (it != value.end()) {
        return std::distance(value.begin(), it);
    }
    return -1;
}

void ByteList::insert(int index, unsigned char item) {
    if (index >= 0 && index <= static_cast<int>(value.size())) {
        value.insert(value.begin() + index, item);
    }
}

void ByteList::removeAt(int index) {
    if (index >= 0 && index < static_cast<int>(value.size())) {
        value.erase(value.begin() + index);
    }
}

void ByteList::add(unsigned char item) {
    value.push_back(item);
}

void ByteList::clear() {
    value.clear();
}

bool ByteList::contains(unsigned char item) const {
    return std::find(value.begin(), value.end(), item) != value.end();
}

std::vector<unsigned char>::iterator ByteList::begin() {
    return value.begin();
}

std::vector<unsigned char>::iterator ByteList::end() {
    return value.end();
}

int ByteList::Count() const {
    return static_cast<int>(value.size());
}

unsigned char ByteList::operator[](int index) const {
    if (index >= 0 && index < static_cast<int>(value.size())) {
        return value[static_cast<size_t>(index)];
    }
    throw std::out_of_range("Index out of range");
}

unsigned char& ByteList::operator[](int index) {
    if (index >= 0 && index < static_cast<int>(value.size())) {
        return value[static_cast<size_t>(index)];
    }
    throw std::out_of_range("Index out of range");
}
