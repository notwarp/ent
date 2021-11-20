//
// Created by Daniele Giuliani on 2/13/21.
//

#ifndef EOES_TYPES_H
#define EOES_TYPES_H

/*
 * System headers required by the following declarations
 * (the implementation will import its specific dependencies):
 */
#include <stdlib.h>
#include <stdbool.h>
#include <uuid/uuid.h>
#include <omp.h>
#include "../console/include/console.h"
/*
 * Application specific headers required by the following declarations
 * (the implementation will import its specific dependencies):
 */
typedef struct TYPE Type;
struct TYPE {
    uuid_t  binuuid;
    char    uuid[UUID_STR_LEN];
};

#include "container/include/container.h"
#include "event/include/event.h"
#include "object/include/object.h"
/* Set EXTERN macro: */
#ifdef CORE_TYPES_IMPORT
#define EXTERN
#else
#define EXTERN extern
#endif

/* Constants declarations here. */

/* Types declarations here. */

/* Global variables declarations here. */

/* Function prototypes here. */

EXTERN void typesInit(void);
bool initSysTypes();
void cleanTypes();
EXTERN Container * createContainer();
EXTERN char *getContainerUUid(Container *container);
EXTERN void destroyContainer(Container *container);
EXTERN void cleanContainerList();
EXTERN Object *createObject();
EXTERN Object *setObjectName(Object *obj, char *name);
EXTERN char *getObjectName(Object *obj);
EXTERN char *getObjectUUid(Object *obj);
EXTERN void destroyObject(Object *obj);
EXTERN void refreshObject(Object *obj);
EXTERN Object *searchObjectByName(const char *name);
EXTERN void cleanObjList();
EXTERN Event * createEvent();
EXTERN char *getEventUUid(Event *evt);
EXTERN void destroyEvent(Event *evt);
EXTERN void cleanEvtList();

EXTERN Container_t *ContainerList;
EXTERN Object_t *ObjList;
EXTERN Event_t *EvtList;

/* Function Usable By this Module */
Type *init_container(Container *container);
Type *init_object(Object *obj);
Type *init_event(Event *evt);

#undef CORE_TYPES_IMPORT
#undef EXTERN
#endif //EOES_TYPES_H
