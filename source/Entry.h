#ifndef ENTRY_H
#define ENTRY_H

#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include "EntryType.h"
#include "Key.h"
#include "Events.h"


class Entry {
public:
    EntryType Type = EntryType::Root;
    std::string Name = "(noname)";
    bool EncodeDescription = true;
    std::string Description = "";
    Key* MyRoot = nullptr;
    Entry* Parent = nullptr;
    std::ofstream ValueStream;

    Entry();
    Entry(EntryType type, const std::string& name);
    Entry(const std::string& name);

    std::string EntryPath() const;

    void setRoot(Key* root);
    virtual void Write(std::ofstream& stream);

    static Entry* Read(std::ifstream& stream, Entry* root, bool isList = false, EntryType listType = EntryType::Empty, bool skipEncDesc = false);

    virtual void ReadValue(std::ifstream& stream);

    virtual void SetValue(const void* value);

    void Clear();

    Key* AsKey();

    virtual ~Entry();

    virtual std::string PrettyPrint(int indent = 0);
};

class BlankEntry : public Entry {
public:
    BlankEntry(const std::string& name);

    void ReadValue(std::ifstream& stream) override;
};

#endif  // ENTRY_H
