#ifndef ENTRYLIST_H
#define ENTRYLIST_H

#include "EntryType.h"
#include "Entry.h"
#include <vector>
#include <iterator>

template <typename T>
class EntryList : public Entry {
public:
    EntryList(const std::string& name);
    void ReadValue(std::ifstream& stream) override;
    void Write(std::ofstream& stream) override;
    void UpdateParents();
    std::string PrettyPrint(int indent = 0) override;

    // IList Implementation
    T& operator[](int index);
    int Count() const;
    bool IsEmpty() const;
    void Add(const T& item);
    void Clear();
    bool Contains(const T& item) const;
    void Remove(const T& item);
    T& Get(int index);
    const T& Get(int index) const;
    void Insert(int index, const T& item);
    int IndexOf(const T& item) const;
    void RemoveAt(int index);

private:
    EntryType type;
    std::vector<T> value;
};

#endif  // ENTRYLIST_H
