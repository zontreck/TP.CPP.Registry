#include "Key.h"

Key::Key(const std::string& name, Entry* parent) : Entry(name) {
    Type = EntryType::Key;
    Parent = parent;
}

Key::Key(const std::string& name) : Entry(name) {
    Type = EntryType::Key;
    Parent = nullptr;
}

void Key::ReplaceEntries(const Entry& replaceWith) {
    if (replaceWith.Type == EntryType::Key) {
        const Key& key = static_cast<const Key&>(replaceWith);
        insert(end(), key.begin(), key.end());
        UpdateRoots();
    }
}


void Key::PlaceAtPath(const std::string& path, Entry& toPlace) {
    if (Type != EntryType::Root) {
        toPlace.MyRoot = MyRoot;
        MyRoot->PlaceAtPath(path, toPlace);
        return;
    }

    std::string pth = path.substr(path.find('/') + 1);

    Key* entry = this;

    while (entry->EntryPath() != path) {
        size_t inx = pth.find('/');
        std::string nextEntryName = pth;
        if (inx != std::string::npos) {
            nextEntryName = pth.substr(0, inx);
            pth = pth.substr(inx + 1);
        }
        else {
            pth.clear();
        }

        auto it = std::find_if(entry->begin(), entry->end(), [&nextEntryName](const Entry& e) {
            return e.Name == nextEntryName;
        });

        if (it == entry->end()) {
            Key nxt(nextEntryName);
            entry->Add(nxt);
            entry = &nxt;
        }
        else {
            entry = &static_cast<Key&>(*it);
        }
    }

    entry->Add(toPlace);
}

bool Key::HasNamedKey(const std::string& name) const {
    auto it = std::find_if(begin(), end(), [&name](const Entry& e) {
        return e.Name == name;
    });
    return it != end();
}

std::string Key::PrettyPrint(int indent) {
    std::string line = Entry::PrettyPrint(indent);
    line += " [" + std::to_string(size()) + "]\n";
    for (Entry& entry : *this) {
        line += entry.PrettyPrint(indent + 4) + "\n";
    }
    return line;
}


const Entry& Key::GetNamed(const std::string& name) const {
    auto it = std::find_if(begin(), end(), [&name](const Entry& e) {
        return e.Name == name;
    });
    if (it != end()) {
        return *it;  // Return a reference to the found Entry
    }
    throw std::runtime_error("Entry not found");
}



void Key::Write(std::ofstream& stream) {
    Entry::Write(stream);
    int entryCount = size();
    stream.write(reinterpret_cast<const char*>(&entryCount), sizeof(entryCount));
    for (Entry& entry : *this) {
        entry.Write(stream);
    }
}

void Key::ReadValue(std::ifstream& stream) {
    int entryCount;
    stream.read(reinterpret_cast<char*>(&entryCount), sizeof(entryCount));
    for (int i = 0; i < entryCount; i++) {
        Entry* entry = Entry::Read(stream, MyRoot);
        entry->Parent = (this);
        entry->MyRoot = (MyRoot);
        Add(*entry);
        delete entry;  // Release the allocated memory
    }
}


void Key::Clear() {
    for (Entry& entry : *this) {
        entry.Parent = (nullptr);
        entry.MyRoot = (nullptr);
    }
    clear();
}

bool Key::IsEmpty() const {
    return empty();
}

Entry& Key::operator[](int index) {
    return at(index);
}

const Entry& Key::operator[](int index) const {
    return at(index);
}

void Key::Add(const Entry& item) {
    if (EventBus::PRIMARY->Post(RegistryEntryAddedEvent(item, GetEntryPath() + "/" + item.GetName()))) {
        return;
    }
    else {
        item.Parent = (this);
        push_back(item);
        UpdateRoots();
    }
}

void Key::RemoveAt(int index) {
    if (index >= 0 && index < size()) {
        const Entry& item = at(index);
        if (EventBus::PRIMARY->Post(RegistryEntryRemovedEvent(item, item.GetEntryPath(), this))) {
            return;
        } else {
            at(index).Parent = (nullptr);
            at(index).MyRoot = (nullptr);
            erase(begin() + index);
            UpdateRoots();
        }
    }
}

void Key::Remove(const Entry& item) {
    auto it = std::find(begin(), end(), item);
    if (it != end()) {
        if (EventBus::PRIMARY->Post(RegistryEntryRemovedEvent(item, item.GetEntryPath(), this))) {
            return;
        } else {
            it->Parent = (nullptr);
            it->MyRoot = (nullptr);
            erase(it);
            UpdateRoots();
        }
    }
}

void Key::Insert(int index, const Entry& item) {
    if (EventBus::PRIMARY->Post(RegistryEntryAddedEvent(item, GetEntryPath() + "/" + item.GetName()))) {
        return;
    } else {
        item.Parent = this;
        insert(begin() + index, item);
        UpdateRoots();
    }
}

int Key::IndexOf(const Entry& item) const {
    auto it = std::find(begin(), end(), item);
    if (it != end()) {
        return std::distance(begin(), it);
    }
    return -1;
}

void Key::UpdateRoots() {
    if (Type == EntryType::Root) {
        setRoot(this);
    }
}
