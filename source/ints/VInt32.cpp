#include "VInt32.h"

VInt32::VInt32(const std::string& name, int value) : Entry(EntryType::Int32, name), Value(value) {}

void VInt32::Write(std::ofstream& stream) {
    Entry::Write(stream);
    stream.write(reinterpret_cast<const char*>(&Value), sizeof(Value));
}

void VInt32::ReadValue(std::ifstream& stream) {
    stream.read(reinterpret_cast<char*>(&Value), sizeof(Value));
}

std::string VInt32::PrettyPrint(int indent) {
    return Entry::PrettyPrint(indent) + " [" + std::to_string(Value) + "]";
}

void VInt32::SetValue(const void* value) {
    Entry::SetValue(value);

    if (value != nullptr) {
        Value = *static_cast<const int*>(value);
    }
}

VInt32* VInt32::SetInt32(int value) {
    Value = value;
    return this;
}
