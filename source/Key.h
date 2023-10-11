#ifndef KEY_H
#define KEY_H

#include "EntryType.h"
#include "Entry.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <exception>
#include <fstream>

class Key : public Entry, public std::vector<Entry> {
public:
    Key(const std::string& name, Entry* parent);
    Key(const std::string& name);
    void ReplaceEntries(const Entry& replaceWith);
    void PlaceAtPath(const std::string& path, Entry& toPlace);
    bool HasNamedKey(const std::string& name) const;
    std::string PrettyPrint(int indent = 0) override;
    const Entry& Key::GetNamed(const std::string& name) const;
    void Write(std::ofstream& stream) override;
    void ReadValue(std::ifstream& stream) override;
    void Clear();
    bool IsEmpty() const;
    Entry& operator[](int index);
    const Entry& operator[](int index) const;
    void Add(const Entry& item);
    void RemoveAt(int index);
    void Remove(const Entry& item);
    void Insert(int index, const Entry& item);
    int IndexOf(const Entry& item) const;



    std::vector<Entry> entries;
private:
    void UpdateRoots();
};

#endif  // KEY_H
