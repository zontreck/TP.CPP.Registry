#include "EntryList.h"

template <typename T>
EntryList<T>::EntryList(const std::string& name) : Entry(name) {
    Type = EntryType::Array;
    Description = "Array";
}

template <typename T>
void EntryList<T>::ReadValue(std::ifstream& stream) {
    stream.read(reinterpret_cast<char*>(&type), sizeof(type));

    if (type == EntryType::Empty) {
        return;
    }

    int count;
    stream.read(reinterpret_cast<char*>(&count), sizeof(count));

    for (int i = 0; i < count; i++) {
        Entry subEntry = Entry::Read(stream, MyRoot, true, type);
        value.push_back(static_cast<T>(subEntry));
        subEntry.SetParent(this);
    }
}

template <typename T>
void EntryList<T>::Write(std::ofstream& stream) {
    Entry::Write(stream);

    if (value.size() > 0) {
        type = value[0].Type;
    }

    stream.write(reinterpret_cast<const char*>(&type), sizeof(type));

    if (type == EntryType::Empty) {
        return;
    }

    int count = value.size();
    stream.write(reinterpret_cast<const char*>(&count), sizeof(count);

    for (const T& entry : value) {
        entry.Write(stream);
    }
}

template <typename T>
void EntryList<T>::UpdateParents() {
    for (Entry& entry : value) {
        entry.SetParent(this);
    }
}

template <typename T>
std::string EntryList<T>::PrettyPrint(int indent) {
    std::string str = Entry::PrettyPrint(indent) + " [ " + std::to_string(value.size()) + " ]\n";

    for (const Entry& entry : value) {
        str += entry.PrettyPrint(indent + 4) + "\n";
    }

    return str;
}

// IList Implementation
template <typename T>
T& EntryList<T>::operator[](int index) {
    return value[index];
}

template <typename T>
int EntryList<T>::Count() const {
    return static_cast<int>(value.size());
}

template <typename T>
bool EntryList<T>::IsEmpty() const {
    return value.empty();
}

template <typename T>
void EntryList<T>::Add(const T& item) {
    value.push_back(item);
}

template <typename T>
void EntryList<T>::Clear() {
    value.clear();
}

template <typename T>
bool EntryList<T>::Contains(const T& item) const {
    return std::find(value.begin(), value.end(), item) != value.end();
}

template <typename T>
void EntryList<T>::Remove(const T& item) {
    value.erase(std::remove(value.begin(), value.end(), item), value.end());
}

template <typename T>
T& EntryList<T>::Get(int index) {
    return value[index];
}

template <typename T>
const T& EntryList<T>::Get(int index) const {
    return value[index];
}

template <typename T>
void EntryList<T>::Insert(int index, const T& item) {
    value.insert(value.begin() + index, item);
}

template <typename T>
int EntryList<T>::IndexOf(const T& item) const {
    auto it = std::find(value.begin(), value.end(), item);
    if (it != value.end()) {
        return static_cast<int>(std::distance(value.begin(), it));
    }
    return -1;
}

template <typename T>
void EntryList<T>::RemoveAt(int index) {
    if (index >= 0 && index < static_cast<int>(value.size())) {
        value.erase(value.begin() + index);
    }
}
