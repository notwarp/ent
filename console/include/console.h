//
// Created by daniele on 2/17/21.
//

#ifndef EOES_CONSOLE_H
#define EOES_CONSOLE_H

#include <stdio.h>

#ifdef CONSOLE_IMPORT
#define EXTERN
#else
#define EXTERN extern
#endif

/* CONSTANTS */
#define AC_RED     "\x1b[31m"
#define AC_GREEN   "\x1b[32m"
#define AC_YELLOW  "\x1b[33m"
#define AC_BLUE    "\x1b[34m"
#define AC_MAGENTA "\x1b[35m"
#define AC_CYAN    "\x1b[36m"
#define AC_RESET   "\x1b[0m"

#ifdef DEBUG
#define Debug if(1)
#define Release if(0)
#else
#define Debug if(0)
#define Release if(1)
#endif

/* FUNCTION PROTOTYPES */

EXTERN void printError(char *message);
EXTERN void printSuccess(char *message);
EXTERN void printWarning(char *message);
EXTERN void printPrimary(char *message);
#undef CONSOLE_IMPORT
#undef EXTERN
#endif //EOES_CONSOLE_H
