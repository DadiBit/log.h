#ifndef _LOG_H__LOG_H
#define _LOG_H__LOG_H

#include <stdio.h>
#include <time.h>

#define LOG_H__COLOR_FILE_LINE 36
#define LOG_H__COLOR_FUNC 35
#define LOG_H__COLOR_TIME 32

#define LOG_H__COLOR_LEVEL_trace 30
#define LOG_H__COLOR_LEVEL_debug 30
#define LOG_H__COLOR_LEVEL_info 34
#define LOG_H__COLOR_LEVEL_warning 33
#define LOG_H__COLOR_LEVEL_error 31
/**
 * You may create custom (case sensitive) levels colors as macros:
 * #define LOG_H__COLOR_LEVEL_toast 32
 */

#define LOG_H__FILE_LINE() \
    printf("\e[0;%dm%s:%d\e[0m", LOG_H__COLOR_FILE_LINE, __FILE__, __LINE__)

/* __func__ must be defined for __STDC_VERSION__ >= 199901L */
#define LOG_H__FUNC() \
    printf("\e[0;%dm[%s]\e[0m", LOG_H__COLOR_FUNC, __func__)

#define LOG_H__LEVEL(level) \
    printf("\e[0;%dm<%s>\e[0m", LOG_H__COLOR_LEVEL_ ## level, #level)

#define LOG_H__TIME() \
    printf("\e[0;%dm@%ld\e[0m", LOG_H__COLOR_TIME, time(NULL))

/* you may edit this macro function to suit your needs directly in the .c source file after undefing it */
#define LOG_H(level) \
    LOG_H__FILE_LINE(), putchar(' '), \
    LOG_H__FUNC(), putchar(' '), \
    LOG_H__LEVEL(level), putchar(' ')

/* log.h public interface */
#define log(level, fmt, args...) \
    LOG_H(level), \
    printf(fmt "\n",##args)

/* shorthands; these also help to lint the levels in the IDE, but they are not required to compile */
#define trace(fmt, args...) log(trace, fmt,##args)
#define debug(fmt, args...) log(debug, fmt,##args)
#define info(fmt, args...) log(info, fmt,##args)
#define warning(fmt, args...) log(warning, fmt,##args)
#define error(fmt, args...) log(error, fmt,##args)

#endif