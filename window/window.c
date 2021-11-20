//
// Created by daniele on 03/10/21.
//

#define CORE_WINDOWS_IMPORT
#include "include/window.h"
#include "window.rapresentation"



bool initSysWindow() {
    Debug printSuccess("INIT SDL AND WINDOW SYSTEM...");
    WinList = calloc(1, sizeof(Win_t));
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        Debug SDL_Log("UNABLE TO INITIALIZE SDL: %s", SDL_GetError());
        return false;
    }else{
        testInitSysWindow();
        Debug printSuccess("INIT SDL SUCCESSFULLY!");
    }
    Release printSuccess("INIT SYS WINDOW COMPLETED");
    SDL_Delay(3000);
    SDL_Quit();
    return true;
}

void pushWindow(Win_t *winList, Win *win) {
    if (winList->win == NULL){
        winList->win = win;
        winList->win_next = NULL;
    }else{
        Win_t *new_node = malloc(sizeof(Win_t));
        winList->win_next = new_node;
        new_node->win = win;
    }
}

Win * createWindow() {
    Win *win = malloc(sizeof(Win));
    if (win)
    {
        win->sdlWin = SDL_CreateWindow("MAIN WINDOW", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500,400, SDL_WINDOW_VULKAN);
        if (win->sdlWin == NULL) {
            Debug printError("SDL WINDOW CREATION FAIL!");
        }else{
            Debug printSuccess("SDL WINDOW CREATION SUCCESS!");
        }
        Debug printSuccess("WINDOW CREATED SUCCESSFULLY!");
        init_window(win);
        pushWindow(WinList, win);
        return win;
    }else{
        Debug printError("CANNOT CREATE WINDOW. WINDOW IS NULL!");
        return NULL;
    }
}

Type *init_window(Win *win)
{
    uuid_generate_random(win->type.binuuid);
    uuid_unparse_upper(win->type.binuuid, win->type.uuid);
    return &win->type;
}

char *getWindowUUID(Win *win)
{
    return win->type.uuid;
}

void destroyWindow(Win *win) {
    free(win);
    win = NULL;
    Debug printSuccess("WINDOW DESTROYED SUCCESSFULLY!");
}

bool testInitSysWindow(){
    Debug printPrimary("UNIT TESTS WINDOW INITIALIZED...");
    Debug printPrimary("CREATING WINDOW...");
    Win *win = createWindow();
    Debug printPrimary("WINDOWS UUID:");
    Debug printWarning(getWindowUUID(win));
    Debug printSuccess("WINDOW CREATED SUCCESSFULLY!");
    if (createInstance(win, "test")){
        Debug printSuccess("VULKAN INSTANCE CREATED SUCCESSFULLY!");
    }else{
        Debug printError("VULKAN INSTANCE CREATION FAILED!");
    }
    if (createSurface(win)){
        Debug printSuccess("VULKAN SURFACE CREATED SUCCESSFULLY!");
    }else{
        Debug printError("VULKAN SURFACE CREATION FAILED!");
    }
    if (win == NULL) {
        return false;
    }else{
        Debug printSuccess("UNIT TESTS WINDOW TERMINATED!");
        return true;
    }
}

void cleanWindowList() {
    Win_t *tmp;
    while (NULL != WinList)
    {
        tmp = WinList;
        WinList = WinList->win_next;
        if (tmp->win) {
            SDL_DestroyWindow(tmp->win->sdlWin);
            vkDestroyInstance(tmp->win->inst, NULL);
        }
        else printWarning("DESTROYING WINDOW SDL OR VULKAN ERROR");
        Debug printPrimary("DESTROYING WINDOW WITH UUID:");
        Debug printWarning(getWindowUUID(tmp->win));
        destroyWindow(tmp->win);
        free(tmp);
    }
}

bool createInstance(Win *win, const char * name) {
    version_r version_ = {
            .major = 1,
            .minor = 1,
            .patch = 70
    };
    /**
     * get required extensions count
     * populate required_extension_names
     * print names of required extensions
     */
    unsigned int required_count;

    if (!SDL_Vulkan_GetInstanceExtensions(win->sdlWin, &required_count, NULL)) {
        Debug printError("CANNOT FIND REQUIRED VULKAN EXTENSION");
        return false;
    }
    printf(AC_BLUE"Required extension count = "AC_YELLOW"%d\n"AC_RESET, required_count);

    const char **required_names = malloc(sizeof(const char *) * required_count);
    if(!required_names) {
        Debug printError("CANNOT CREATE REQUIRED_NAMES VARIABLE");
        return false;
    }

    // get names of required extensions
    if(!SDL_Vulkan_GetInstanceExtensions(win->sdlWin, &required_count, required_names)) {
        Debug printError("CANNOT FIND A COMPATIBLE VULKAN EXTENSIONS AFTER");
        return false;
    }
    // print required extension names
    for(size_t i = 0; i < required_count; i++) {
        printf(AC_GREEN"\t%s\n"AC_RESET, required_names[i]);
    }

    /**
     * get available extensions count
     * populate available_extension_names
     * print names of available extensions
     */
    unsigned int available_count;
    VkResult result;
    result = vkEnumerateInstanceExtensionProperties(NULL, &available_count, NULL);
    if (result != VK_SUCCESS) {
        Debug printError("CANNOT COUNT AVAILABLE EXTENSIONS");
    };
    printf(AC_BLUE"Available extension count = "AC_YELLOW"%d\n"AC_RESET, available_count);

    // get names of available extensions
    VkExtensionProperties available_names[available_count];
    result = vkEnumerateInstanceExtensionProperties(NULL, &available_count, available_names);
    if (result != VK_SUCCESS) {
        Debug printError("CANNOT COUNT AVAILABLE EXTENSIONS");
    };
    // print available extension names
    for(size_t i = 0; i < available_count; i++) {
        printf(AC_GREEN"\t%s\n"AC_RESET, available_names[i].extensionName);
    }

    win->appInfo = (VkApplicationInfo) {
            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pNext = NULL,
            .pApplicationName = name,
            .applicationVersion = 1,
            .pEngineName = NULL,
            .engineVersion = 0,
            .apiVersion = VK_MAKE_VERSION(version_.major, version_.minor, version_.patch),
    };

    win->createInstanceInfo = (VkInstanceCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pNext = NULL,
            .flags = 0,
            .pApplicationInfo = &win->appInfo,
            .enabledExtensionCount = required_count,
            .ppEnabledExtensionNames = required_names,
            .enabledLayerCount = 0,
            .ppEnabledLayerNames = NULL,
    };
    win->res = vkCreateInstance(&win->createInstanceInfo, NULL, &win->inst);
    if (!enableValidationLayers(&win->createInstanceInfo)) {
        Debug printError("validation layers Problem!");
    }
    free(required_names);
    return true;
}

bool createSurface(Win *win){
    if (!SDL_Vulkan_CreateSurface(win->sdlWin, win->inst, &win->surface)) {
        return false;
    }
    return true;
}

bool enableValidationLayers(VkInstanceCreateInfo *createInstanceInfo) {
    int validation_layer_count = 1;
    const char *validationLayers[validation_layer_count];
    validationLayers[0] = "VK_LAYER_LUNARG_standard_validation";

    #ifdef NDEBUG
        const bool enableValidationLayers = false;
        printf(AC_BLUE"VULKAN VALIDATION LAYER DEBUG NOT ENABLED\n"AC_RESET);
        return true;
    #else
        const bool enableValidationLayers = true;
        Debug printPrimary("REQUESTED VALIDATION LAYER:");
        // print available validation layer names
        for(size_t i = 0; i < 1; i++) {
            printf(AC_BLUE"\t%s\n"AC_RESET, validationLayers[i]);
        }
        return checkValidationLayerSupport(createInstanceInfo, validationLayers);
    #endif
}

bool checkValidationLayerSupport(VkInstanceCreateInfo *createInstanceInfo, const char *validationLayers[]) {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, NULL);

    VkLayerProperties availableLayers[layerCount];
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers);

    Debug printPrimary("AVAILABLE VALIDATION LAYER:");
    // print available extension names
    for(size_t i = 0; i < layerCount; i++) {
        printf(AC_BLUE"\t%s\n"AC_RESET, availableLayers[i].layerName);
    }

    for (int x = 0; x < 1; x++) {
        bool layerFound = false;

        for (int i = 0; i < layerCount; ++i) {
            if (strcmp(validationLayers[x], availableLayers[i].layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }
    return true;
}