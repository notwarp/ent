//
// Created by daniele on 02/10/21.
//

#include "include/container.h"
#include "container.rapresentation"

bool initSysContainer() {
    ContainerList = calloc(1, sizeof(Container_t));
    if (ContainerList){
        Debug testInitSysContainer(ContainerList);
        return true;
    }else{
        return false;
    }
}

void pushContainer(Container_t *containerList, Container *container) {
    if (containerList->container == NULL){
        containerList->container = container;
        containerList->container_next = NULL;
    }else{
        Container_t *new_node = malloc(sizeof(Container_t));
        containerList->container_next = new_node;
        new_node->container = container;
    }
}

Container *createContainer()
{
    Container *container = malloc(sizeof(Container));
    if (container)
    {
        Debug printSuccess("CONTAINER CREATED SUCCESSFULLY!");
        init_container(container);
        pushContainer(ContainerList, container);
        return container;
    }else{
        Debug printError("CANNOT CREATE CONTAINER. CONTAINER IS NULL!");
        return NULL;
    }
}

Type *init_container(Container *container)
{
    uuid_generate_random(container->type.binuuid);
    uuid_unparse_upper(container->type.binuuid, container->type.uuid);
    return &container->type;
}

void destroyContainer(Container *container) {
    free(container);
    container = NULL;
    Debug printSuccess("CONTAINER DESTROYED SUCCESSFULLY!");
}

char *getContainerUUid(Container *container)
{
    return container->type.uuid;
}

bool testInitSysContainer(){
    Debug printPrimary("UNIT TESTS CONTAINER INITIALIZED...");
    Debug printPrimary("CREATING CONTAINER...");
    Container *container = createContainer();
    init_container(container);
    //setContainerName(evt, "test");
    //Container *evt2 = createContainer();
    //init_event(evt2);
    //setContainerName(evt2, "test2");
    Debug printPrimary("CONTAINER UUID:");
    Debug printWarning(getContainerUUid(container));
    Debug printSuccess("CONTAINER CREATED SUCCESSFULLY!");
    //Object * result = searchObjectByName("test");
    //char* message;
    //message = calloc(strlen("OBJECT FOUND:")+strlen(getObjectName(result))+1, sizeof(char));
    //strcpy(message, "OBJECT FOUND:");
    //strcat(message, getObjectName(result));
    //Debug printSuccess(message);
    //free(message);
    if (container == NULL) {
        return false;
    }else{
        Debug printSuccess("UNIT TESTS CONTAINER TERMINATED!");
        return true;
    }
}

void cleanContainerList() {
    Container_t *tmp;
    while (NULL != ContainerList)
    {
        tmp = ContainerList;
        ContainerList = ContainerList->container_next;
        destroyContainer(tmp->container);
        free(tmp);
    }
}