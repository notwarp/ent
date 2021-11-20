//
// Created by Daniele Giuliani on 2/13/21.
//

#ifndef EOES_OBJECT_H
#define EOES_OBJECT_H
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include <stdbool.h>
#include <uuid/uuid.h>
/* TYPES */

typedef struct OBJECT Object;
typedef struct OBJECT_T Object_t;
/* FUNCTIONS */

bool initSysObject();
bool testInitSysObject();
void pushObject(Object_t *obj_list, Object *obj);
int getCount(Object_t *obj_list);

#endif //EOES_OBJECT_H
