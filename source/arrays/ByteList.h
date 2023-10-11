#ifndef BYTELIST_H
#define BYTELIST_H

#include "../Entry.h"
#include <vector>

class ByteList : public Entry {
public:
    ByteList(const std::string& name);

    void ReadValue(std::ifstream& stream) override;
    void Write(std::ofstream& stream) override;
    std::string PrettyPrint(int indent = 0) override;

    int indexOf(unsigned char item) const;
    void insert(int index, unsigned char item);
    void removeAt(int index);
    void add(unsigned char item);
    void clear();
    bool contains(unsigned char item) const;
    std::vector<unsigned char>::iterator begin();
    std::vector<unsigned char>::iterator end();

    int Count() const; // Equivalent to Value.Count in C#
    unsigned char operator[](int index) const; // Equivalent to Value[index] in C#
    unsigned char& operator[](int index); // Equivalent to Value[index] in C#

private:
    std::vector<unsigned char> value;
};

#endif
