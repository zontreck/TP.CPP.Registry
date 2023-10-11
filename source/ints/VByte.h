#ifndef VBYTE_H
#define VBYTE_H

#include "../Entry.h"

class VByte : public Entry {
public:
    VByte(const std::string& name, unsigned char value);
    unsigned char Value;

    void Write(std::ofstream& stream) override;
    void ReadValue(std::ifstream& stream) override;
    std::string PrettyPrint(int indent = 0) override;
    void SetValue(const void* value) override;
    VByte* SetByte(unsigned char value);
};

#endif  // VBYTE_H
