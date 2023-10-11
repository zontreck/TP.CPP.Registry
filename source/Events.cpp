#include "Events.h"
#include <tpeventbus/EventBus.h>
#include "Key.h"


using namespace std;


bool RegistryLoadedEvent::post()
{
    EventBus<RegistryLoadedEvent> bus = EventBus<RegistryLoadedEvent>::GetInstance();
    return bus.Post(*this);
}

RegistryLoadedEvent::RegistryLoadedEvent(Key* _root) 
{
    root = _root;
}


RegistrySavedEvent::RegistrySavedEvent(Key* _root, std::string filename)
{
    root = _root;
    file = filename;
}

bool RegistrySavedEvent::post()
{
    EventBus<RegistrySavedEvent> bus = EventBus<RegistrySavedEvent>::GetInstance();
    return bus.Post(*this);
}


RegistryEntryAddedEvent::RegistryEntryAddedEvent(Entry* nEntry, std::string path){
    newEntry = nEntry;
    MyPath = path;
}

bool RegistryEntryAddedEvent::post()
{
    EventBus<RegistryEntryAddedEvent> bus = EventBus<RegistryEntryAddedEvent>::GetInstance();
    return bus.Post(*this);
}