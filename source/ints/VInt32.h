#ifndef VINT32_H
#define VINT32_H

#include "../Entry.h"

class VInt32 : public Entry {
public:
    VInt32(const std::string& name, int value);
    int Value;

    void Write(std::ofstream& stream) override;
    void ReadValue(std::ifstream& stream) override;
    std::string PrettyPrint(int indent = 0) override;
    void SetValue(const void* value) override;
    VInt32* SetInt32(int value);
};

#endif  // VINT32_H
