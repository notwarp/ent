//
// Created by daniele on 2/17/21.
//
#define CONSOLE_IMPORT
#include "include/console.h"

void printError(char *message)
{
    printf(AC_RED"%s\n"AC_RESET, message);
}
void printSuccess(char *message)
{
    printf(AC_GREEN"%s\n"AC_RESET, message);
}

void printWarning(char *message)
{
    printf(AC_YELLOW"%s\n"AC_RESET, message);
}
void printPrimary(char *message)
{
    printf(AC_CYAN"%s\n"AC_RESET, message);
}