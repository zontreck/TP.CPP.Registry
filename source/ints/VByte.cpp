#include "VByte.h"

VByte::VByte(const std::string& name, unsigned char value) : Entry(EntryType::Byte, name), Value(value) {}

void VByte::Write(std::ofstream& stream) {
    Entry::Write(stream);
    stream.write(reinterpret_cast<const char*>(&Value), sizeof(Value));
}

void VByte::ReadValue(std::ifstream& stream) {
    stream.read(reinterpret_cast<char*>(&Value), sizeof(Value));
}

std::string VByte::PrettyPrint(int indent) {
    return Entry::PrettyPrint(indent) + " [" + std::to_string(Value) + "]";
}

void VByte::SetValue(const void* value) {
    Entry::SetValue(value);

    if (value != nullptr) {
        Value = *static_cast<const unsigned char*>(value);
    }
}

VByte* VByte::SetByte(unsigned char value) {
    Value = value;
    return this;
}
