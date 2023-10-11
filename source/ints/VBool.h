#ifndef VBOOL_H
#define VBOOL_H

#include "../Entry.h"

class VBool : public Entry {
public:
    VBool(const std::string& name, bool value);
    bool Value;

    void Write(std::ofstream& stream) override;
    void ReadValue(std::ifstream& stream) override;
    std::string PrettyPrint(int indent = 0) override;
    void SetValue(const void* value) override;
    VBool* SetBool(bool value);
};

#endif  // VBOOL_H
