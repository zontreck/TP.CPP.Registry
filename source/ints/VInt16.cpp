#include "VInt16.h"

VInt16::VInt16(const std::string& name, short value) : Entry(EntryType::Int16, name), Value(value) {}

void VInt16::Write(std::ofstream& stream) {
    Entry::Write(stream);
    stream.write(reinterpret_cast<const char*>(&Value), sizeof(Value));
}

void VInt16::ReadValue(std::ifstream& stream) {
    stream.read(reinterpret_cast<char*>(&Value), sizeof(Value));
}

std::string VInt16::PrettyPrint(int indent) {
    return Entry::PrettyPrint(indent) + " [" + std::to_string(Value) + "]";
}

void VInt16::SetValue(const void* value) {
    Entry::SetValue(value);

    if (value != nullptr) {
        Value = *static_cast<const short*>(value);
    }
}

VInt16* VInt16::SetInt16(short value) {
    Value = value;
    return this;
}
