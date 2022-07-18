#define TIMBER_ENABLE_SHORTHANDS
#include "log.h"

/* we need to undefine it first to avoid compiler warnings */
#undef LOG_H
/** 
 * LOG_H is a macro called internally by log (which itself is called by trace/debug/info...)
 * and is responsable of what's print before the actual message.
 * ! Don't place a comma after last function call.
 */
#define LOG_H(level) \
    LOG_H__FILE_LINE(), putchar(' '), \
    LOG_H__TIME(), putchar(' '), \
    printf("{My application} "), \
    LOG_H__FUNC(), putchar(' '), \
    LOG_H__LEVEL(level), putchar(' ')

int main () {
    debug("Hello, World!");
    char *str = "log.h is amazing!";
    log(warning, "Format like printf: `%s`", str);
    return 0;
}