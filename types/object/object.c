//
// Created by Daniele Giuliani on 2/13/21.
//
#include "include/object.h"
#include "object.rapresentation"

bool initSysObject()
{
    ObjList = calloc(1, sizeof(Object_t));
    if (ObjList){
        Debug testInitSysObject(ObjList);
        return true;
    }else{
        return false;
    }
}

void pushObject(Object_t *obj_list, Object *obj)
{
    if (obj_list->obj == NULL){
        obj_list->obj = obj;
        obj_list->obj_next = NULL;
    }else{
        Object_t *new_node = malloc(sizeof(Object_t));
        obj_list->obj_next = new_node;
        new_node->obj = obj;
        new_node->obj_next = NULL;
    }
}

Object *createObject(void)
{

    Object *obj=malloc(sizeof(Object));

    if (obj){
        init_object(obj);
        pushObject(ObjList, obj);
        return obj;
    }else{
        return NULL;
    }
}

Type *init_object(Object *obj)
{
    uuid_generate_random(obj->type.binuuid);
    uuid_unparse_upper(obj->type.binuuid, obj->type.uuid);
    return &obj->type;
}

void refreshObject(Object *obj)
{
    init_object(obj);
}

Object *setObjectName(Object *obj, char *name)
{
    obj->name = name;
    return obj;
}

char *getObjectName(Object *obj)
{
    if (obj)
    {
        return obj->name;
    }else{
        Debug printWarning("Object is NULL!");
        return "NULL";
    }
}

void destroyObject(Object *obj)
{
    free(obj);
    obj = NULL;
}

char *getObjectUUid(Object *obj)
{
    return obj->type.uuid;
}

int getCount(Object_t *obj_list)
{
    if (obj_list == NULL) {
        return 0;
    }else {
        return 1 + getCount(obj_list->obj_next);
    }
}

/**
 * @param name
 * @return
 */
Object *searchObjectByName(const char * name)
{
    Object *obj;
    Object_t *current_obj_t = ObjList;
    if (!current_obj_t->obj) {
        Debug printWarning("Warning: ->obj is NULL");
        return NULL;
    }else{
        while (1)
        {
            if (current_obj_t->obj->name == name) {
                obj = current_obj_t->obj;
                break;
            } else {
                current_obj_t = current_obj_t->obj_next;
            }
        }
        return obj;
    }
}

bool testInitSysObject(){
    Debug printPrimary("UNIT TESTS OBJECT INITIALIZED...");
    Debug printPrimary("CREATING OBJECT...");
    Object *ob = createObject();
    init_object(ob);
    setObjectName(ob, "test");
    Object *ob2 = createObject();
    setObjectName(ob2, "test2");
    Debug printPrimary("OBJECT UUID:");
    Debug printWarning(getObjectUUid(ob));
    Debug printSuccess("OBJECT CREATED SUCCESSFULLY!");
    Object * result = searchObjectByName("test");
    char* message;
    message = calloc(strlen("OBJECT FOUND:")+strlen(getObjectName(result))+1, sizeof(char));
    strcpy(message, "OBJECT FOUND:");
    strcat(message, getObjectName(result));
    Debug printSuccess(message);
    free(message);
    if (ob == NULL) return false;
    else{
        Debug printSuccess("UNIT TESTS OBJECT TERMINATED!");
        return true;
    }
}

void cleanObjList() {
    Object_t *tmp;
    while (NULL != ObjList)
    {
        tmp = ObjList;
        ObjList = ObjList->obj_next;
        destroyObject(tmp->obj);
        free(tmp);
    }
}