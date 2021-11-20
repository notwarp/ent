//
// Created by Daniele Giuliani on 2/13/21.
//
#define CORE_TYPES_IMPORT
#include "types.h"

bool initSysTypes()
{
    bool check = true;

    if (!initSysContainer())
    {
        check = false;
    }
    if (!initSysObject())
    {
        check = false;
    }
    if (!initSysEvent())
    {
        check = false;
    }
    cleanTypes();
    return check;
}

void cleanTypes() {
    cleanContainerList();
    cleanObjList();
    cleanEvtList();
}