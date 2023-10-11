#include "Word.h"

Word::Word(const std::string& name, const std::string& value) : Entry(EntryType::Word, name), Value(value) {}

void Word::Write(std::ofstream& stream) {
    Entry::Write(stream);
    stream << Value;
}

void Word::ReadValue(std::ifstream& stream) {
    std::getline(stream, Value);
}

std::string Word::PrettyPrint(int indent) {
    return Entry::PrettyPrint(indent) + " [" + Value + "]";
}

void Word::SetValue(const void* value) {
    Entry::SetValue(value);

    if (value != nullptr) {
        const char* str = static_cast<const char*>(value);
        Value = str;
    }
}

Word* Word::SetWord(const std::string& value) {
    Value = value;
    return this;
}
