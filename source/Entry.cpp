#include "Entry.h"
#include "EntryType.h"
#include "Word.h"
#include "Integers.h"
#include "EntryList.h"
#include "Key.h"
#include "Arrays.h"
#include <stdexcept>

Entry::Entry() {
    Type = EntryType::Root;
    Name = "root";
    Description = "Registry Root";
    Parent = nullptr;
    MyRoot = nullptr;
}

Entry::Entry(EntryType type, const std::string& name) : Type(type), Name(name) {}

Entry::Entry(const std::string& name) : Name(name)
{

}
std::string Entry::EntryPath() const {
    std::stack<const Entry*> stack;
    const Entry* current = this;

    while (current != nullptr) {
        stack.push(current);
        current = current->Parent;
    }

    std::string path = "";
    while (!stack.empty()) {
        std::string next = stack.top()->Name;
        stack.pop();

        path = path + "/" + next;
        if (!path.empty() && path[0] == '/') {
            path = path.substr(1);
        }
    }

    return path;
}

void Entry::setRoot(Key* root) {
    MyRoot = root;

    if (this->Type == EntryType::Key) {
        Key* keyEntry = static_cast<Key*>(this);
        for (Entry &entry : keyEntry->entries) {
            entry.setRoot(root);
        }
    }
}



Entry* Entry::Read(std::ifstream& stream, Entry* root, bool isList, EntryType listType, bool skipEncDesc) {
    Entry* entry = nullptr;
    EntryType Type = listType;
    std::string Name;
    std::string Description;
    bool EncodeDesc = true;

    if (!isList) {
        Type = static_cast<EntryType>(stream.get());
        std::getline(stream, Name);

        if (Type == EntryType::Root && !skipEncDesc) {
            EncodeDesc = static_cast<bool>(stream.get());
        }

        if (skipEncDesc) {
            EncodeDesc = true;
        }

        if (root == nullptr) {
            if (EncodeDesc) {
                std::getline(stream, Description);
            }
        }

        if (root != nullptr && root->EncodeDescription) {
            std::getline(stream, Description);
        }
    }

    switch (Type) {
        case EntryType::Key:
            entry = new Key(Name);
            break;
        case EntryType::Word:
            entry = new Word(Name, "");
            break;
        case EntryType::Int16:
            entry = new VInt16(Name, 0);
            break;
        case EntryType::Int32:
            entry = new VInt32(Name, 0);
            break;
        case EntryType::Int64:
            entry = new VInt64(Name, 0);
            break;
        case EntryType::Bool:
            entry = new VBool(Name, false);
            break;
        case EntryType::Byte:
            entry = new VByte(Name, 0);
            break;
        case EntryType::Root:
            entry = new Key("root");
            break;
        case EntryType::Array:
            entry = new EntryList<Entry>(Name);
            break;
        case EntryType::WordArray:
            entry = new WordList(Name);
            break;
        case EntryType::ByteArray:
            entry = new ByteList(Name);
            break;
        default:
            entry = new BlankEntry(Name);
            break;
    }

    entry->Type = Type;
    entry->Description = Description;
    entry->EncodeDescription = EncodeDesc;
    entry->Parent = nullptr;

    if (entry->Type == EntryType::Root) {
        entry->MyRoot = entry->AsKey();
    }

    entry->ReadValue(stream);
    return entry;
}

void Entry::ReadValue(std::ifstream& stream) {}


void Entry::SetValue(const void* value) {}

void Entry::Clear() {}

Entry::~Entry() {}

std::string Entry::PrettyPrint(int indent) {
    return std::string(indent, ' ') + "[" + std::to_string(static_cast<int>(Type)) + "] " + Name;
}

BlankEntry::BlankEntry(const std::string& name) : Entry(EntryType::Empty, name) {}

void BlankEntry::ReadValue(std::ifstream& stream) {}



Key* Entry::AsKey()
{
    return static_cast<Key*>(this);
}