//
// Created by daniele on 03/10/21.
//

#ifndef ENT_WINDOW_H
#define ENT_WINDOW_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>
#include <stdio.h>
#include "string.h"
#include <stdbool.h>
#include <uuid/uuid.h>
#include "../../console/include/console.h"
#include "../../types/types.h"

#ifdef CORE_WINDOWS_IMPORT
#define EXTERN
#else
#define EXTERN extern
#endif

typedef struct VERSION_T version_r;
typedef struct QUEUE_FAMILY_INDICES QueueFamilyIndices;
typedef struct DEVICE_RATE_T {
    uint32_t rate;
    VkPhysicalDevice device;
} DeviceRateList;
typedef struct WINDOW Win;
typedef struct WINDOW_T Win_t;

bool initSysWindow();
bool testInitSysWindow();
Type * init_window(Win * win);

Win * createWindow();
char * getWindowUUID(Win * win);
void destroyWindow(Win * win);
void cleanWindowList();
bool createInstance(Win *win, const char * name);
bool pickPhysicalDevice(Win *win);
bool isDeviceSuitable(VkPhysicalDevice device);
VkPhysicalDevice getBestDeviceByRate(DeviceRateList candidates[], uint32_t count);
uint32_t rateDeviceSuitability(VkPhysicalDevice device);
QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
bool createSurface(Win *win);
bool enableValidationLayers(VkInstanceCreateInfo *createInstanceInfo);
bool checkValidationLayerSupport(VkInstanceCreateInfo *createInstanceInfo, const char *validationLayers[]);
EXTERN Win_t * WinList;
#undef CORE_WINDOWS_IMPORT
#undef EXTERN
#endif //ENT_WINDOW_H
