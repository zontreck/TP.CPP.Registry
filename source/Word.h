#ifndef WORD_H
#define WORD_H

#include "Entry.h"

class Word : public Entry {
public:
    Word(const std::string& name, const std::string& value);
    std::string Value;

    void Write(std::ofstream& stream) override;
    void ReadValue(std::ifstream& stream) override;
    std::string PrettyPrint(int indent = 0) override;
    void SetValue(const void* value) override;
    Word* SetWord(const std::string& value);
};

#endif  // WORD_H
