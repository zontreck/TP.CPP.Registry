#include "VBool.h"

VBool::VBool(const std::string& name, bool value) : Entry(EntryType::Bool, name), Value(value) {}

void VBool::Write(std::ofstream& stream) {
    Entry::Write(stream);
    stream.write(reinterpret_cast<const char*>(&Value), sizeof(Value));
}

void VBool::ReadValue(std::ifstream& stream) {
    stream.read(reinterpret_cast<char*>(&Value), sizeof(Value));
}

std::string VBool::PrettyPrint(int indent) {
    return Entry::PrettyPrint(indent) + " [" + std::to_string(Value) + "]";
}

void VBool::SetValue(const void* value) {
    Entry::SetValue(value);

    if (value != nullptr) {
        Value = *static_cast<const bool*>(value);
    }
}

VBool* VBool::SetBool(bool value) {
    Value = value;
    return this;
}
