#include "VInt64.h"

VInt64::VInt64(const std::string& name, long long value) : Entry(EntryType::Int64, name), Value(value) {}

void VInt64::Write(std::ofstream& stream) {
    Entry::Write(stream);
    stream.write(reinterpret_cast<const char*>(&Value), sizeof(Value));
}

void VInt64::ReadValue(std::ifstream& stream) {
    stream.read(reinterpret_cast<char*>(&Value), sizeof(Value));
}

std::string VInt64::PrettyPrint(int indent) {
    return Entry::PrettyPrint(indent) + " [" + std::to_string(Value) + "]";
}

void VInt64::SetValue(const void* value) {
    Entry::SetValue(value);

    if (value != nullptr) {
        Value = *static_cast<const long long*>(value);
    }
}

VInt64* VInt64::SetInt64(long long value) {
    Value = value;
    return this;
}
