#ifndef VINT16_H
#define VINT16_H

#include "../Entry.h"

class VInt16 : public Entry {
public:
    VInt16(const std::string& name, short value);
    short Value;

    void Write(std::ofstream& stream) override;
    void ReadValue(std::ifstream& stream) override;
    std::string PrettyPrint(int indent = 0) override;
    void SetValue(const void* value) override;
    VInt16* SetInt16(short value);
};

#endif  // VINT16_H
