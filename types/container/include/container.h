//
// Created by daniele on 02/10/21.
//

#ifndef ENT_CONTAINER_H
#define ENT_CONTAINER_H
#include <stdbool.h>
#include <stdlib.h>

typedef struct CONTAINER Container;
typedef struct CONTAINER_T Container_t;

bool initSysContainer();
void pushContainer(Container_t *containerList, Container *container);
bool testInitSysContainer();
#endif //ENT_CONTAINER_H
