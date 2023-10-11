#ifndef EVENTS_H
#define EVENTS_H

#include <tpeventbus/Event.h>
#include <string>
#include "Key.h"

using namespace std;


class RegistryLoadedEvent : public Event
{
public:
    RegistryLoadedEvent(Key* _root);
    bool post() override;

    Key* root;
};

class RegistrySavedEvent : public Event
{
public:
    RegistrySavedEvent(Key* _root, std::string filename);
    bool post() override;

    Key* root;
    std::string file;
};


class RegistryEntryAddedEvent : public Event
{
public:
    RegistryEntryAddedEvent(Entry *nEntry, std::string path);
    bool post() override;

    Entry* newEntry;
    std::string MyPath;
};

class RegistryEntryRemovedEvent : public Event
{
public:
    RegistryEntryRemovedEvent(Entry *oEntry, std::string path, Key *oParent);
    bool post() override;

    Entry* oldEntry;
    std::string oldPath;
    Key* oldParent;
};



#endif