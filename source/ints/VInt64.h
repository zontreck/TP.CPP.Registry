#ifndef VINT64_H
#define VINT64_H

#include "../Entry.h"

class VInt64 : public Entry {
public:
    VInt64(const std::string& name, long long value);
    long long Value;

    void Write(std::ofstream& stream) override;
    void ReadValue(std::ifstream& stream) override;
    std::string PrettyPrint(int indent = 0) override;
    void SetValue(const void* value) override;
    VInt64* SetInt64(long long value);
};

#endif  // VINT64_H
