//
// Created by Daniele Giuliani on 2/13/21.
//

#ifndef EOES_EVENT_H
#define EOES_EVENT_H

#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include <stdbool.h>
#include <uuid/uuid.h>

typedef struct EVENT Event;
typedef struct EVENT_T Event_t;

bool initSysEvent();
void pushEvent(Event_t *evt_list, Event *evt);

bool testInitSysEvent();

#endif //EOES_EVENT_H
