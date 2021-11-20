#include <stdio.h>
#include "console/include/console.h"
#include "types/types.h"
#include "window/include/window.h"

int main(void) {
    Debug printSuccess("INIT MAIN...");
    initSysTypes();
    initSysWindow();
    cleanWindowList();
    return 0;
}
