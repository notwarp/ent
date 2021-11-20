//
// Created by Daniele Giuliani on 2/13/21.
//
#include "include/event.h"
#include "event.rapresentation"

bool initSysEvent(){
    EvtList = calloc(1, sizeof (Event_t));
    if (EvtList) {
        Debug testInitSysEvent(EvtList);
        return true;
    }else{
        Debug printWarning("UNIT TESTS EVENT SOMETHING WENT WRONG!");
        return false;
    }
}

void pushEvent(Event_t *evt_list, Event *evt) {
    if (evt_list->evt == NULL){
        evt_list->evt = evt;
        evt_list->evt_next = NULL;
    }else{
        Event_t *new_node = malloc(sizeof(Event_t));
        evt_list->evt_next = new_node;
        new_node->evt = evt;
    }
}

Event *createEvent()
{
    Event *evt = malloc(sizeof(Event));
    if (evt)
    {
        Debug printSuccess("EVENT CREATED SUCCESSFULLY!");
        init_event(evt);
        pushEvent(EvtList, evt);
        return evt;
    }else{
        Debug printError("CANNOT CREATE EVENT. EVENT IS NULL!");
        return NULL;
    }
}
Type *init_event(Event *evt)
{
    uuid_generate_random(evt->type.binuuid);
    uuid_unparse_upper(evt->type.binuuid, evt->type.uuid);
    return &evt->type;
}
void destroyEvent(Event *evt) {
    free(evt);
    evt = NULL;
    Debug printSuccess("EVENT DESTROYED SUCCESSFULLY!");
}

char *getEventUUid(Event *evt)
{
    return evt->type.uuid;
}

bool testInitSysEvent(){
    Debug printPrimary("UNIT TESTS EVENT INITIALIZED...");
    Debug printPrimary("CREATING EVENT...");
    Event *evt = createEvent();
    init_event(evt);
    //setEventName(evt, "test");
    //Event *evt2 = createEvent();
    //init_event(evt2);
    //setEventName(evt2, "test2");
    Debug printPrimary("EVENT UUID:");
    Debug printWarning(getEventUUid(evt));
    Debug printSuccess("EVENT CREATED SUCCESSFULLY!");
    //Object * result = searchObjectByName("test");
    //char* message;
    //message = calloc(strlen("OBJECT FOUND:")+strlen(getObjectName(result))+1, sizeof(char));
    //strcpy(message, "OBJECT FOUND:");
    //strcat(message, getObjectName(result));
    //Debug printSuccess(message);
    //free(message);
    if (evt == NULL) {
        return false;
    }else{
        Debug printSuccess("UNIT TESTS EVENT TERMINATED!");
        return true;
    }
}

void cleanEvtList() {
    Event_t *tmp;
    while (NULL != EvtList)
    {
        tmp = EvtList;
        EvtList = EvtList->evt_next;
        destroyEvent(tmp->evt);
        free(tmp);
    }
}