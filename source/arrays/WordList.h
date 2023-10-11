#ifndef WORDLIST_H
#define WORDLIST_H

#include "../Entry.h"
#include <string>
#include <vector>

class WordList : public Entry {
public:
    WordList(const std::string& name);

    void ReadValue(std::ifstream& stream) override;
    void Write(std::ofstream& stream) override;
    std::string PrettyPrint(int indent = 0) override;

    int indexOf(const std::string& item) const;
    void insert(int index, const std::string& item);
    void removeAt(int index);
    void add(const std::string& item);
    void clear();
    bool contains(const std::string& item) const;
    std::vector<std::string>::iterator begin();
    std::vector<std::string>::iterator end();

private:
    std::vector<std::string> value;
};

#endif
