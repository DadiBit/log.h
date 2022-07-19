#ifndef _LOG_H__LOG_H
#define _LOG_H__LOG_H

#include <stdio.h>
#include <time.h>

/**
 * # Start of modules configuration
 * 
 * Each module is a macro function that returns a printf-like
 * format string and the optional arguments to it.
 * 
 * Special module variables are:
 * - level: the level of the message
 * - file/line: the file/line where log was called
 * - func: the function in which log was called
 * - epoch: the UNIX epoch returned from `time(NULL)`
 * 
 * Please note that a maxiumum of 8 variables aer allowed
 */

#define MOD_LEVEL() "<%s> ", level
#define MOD_LEVEL_COLOR(level) \
    level == "error" \
        ? FG(RED) : \
    level == "warn" \
        ? FG(YELLOW) : \
    level == "info" \
        ? FG(BLUE) : \
    level == "debug" \
        ? FG(BLACK, BRIGHT) : \
    FG(WHITE)

#define MOD_FILE() "%s:%d ", file, line
#define MOD_FILE_COLOR(file, line) FG(CYAN)

#define MOD_FUNC() "[%s] ", func
#define MOD_FUNC_COLOR(func) FG(MAGENTA)

#define MOD_TIME() "%ld ", epoch
#define MOD_TIME_COLOR(epoch) FG(GREEN)

#define MODULES() \
    MOD_FILE, MOD_FUNC, MOD_LEVEL

/* End of configuration */
/* Start of magic tricks */

// MACRO utilites
#define EXPAND2(x...) x
#define EXPAND(x...) EXPAND2(x)
#define STR2(x) #x
#define STR(x) STR2(x)

// this helps the ForEach/Map like functions
#define _LOG_H_FE(_1, _2, _3, _4, _5, _6, _7, _8, F, ...) F

// ANSI quick Colors
// See: https://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters
#define BLACK 0
#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define WHITE 7

#define RESET "\e[0m"

// you may call `FG(n)` for code 3n and `FG(n, BRIGHT)` for code 9n
#define BRIGHT BRIGHT
#define _FG_ "3"
#define _FG_BRIGHT "9"
#define FG(code, tone...) "\e[" _FG_##tone STR(code) "m"
#define _BG_ "4"
#define _BG_BRIGHT "10"
#define BG(code, tone...) "\e[" _BG_##tone STR(code) "m"

// V = Module Variable
#define _LOG_H_V_level(level, ...) level
#define _LOG_H_V_epoch(_0, epoch, ...) epoch
#define _LOG_H_V_file(...) __FILE__
#define _LOG_H_V_line(...) __LINE__
#define _LOG_H_V_func(...) __func__
// #define _LOG_H_V_pi(...) 3.1415

// VP = Module Variable Parse
// See: https://github.com/yabadabu/for_each/blob/master/for_each.h and https://stackoverflow.com/questions/6707148/foreach-macro-on-macros-arguments
#define _LOG_H_VP1(F, A, a) F(a) A
#define _LOG_H_VP2(F, A, a, b...) F(a) A, _LOG_H_VP1(F, A, b)
#define _LOG_H_VP3(F, A, a, b...) F(a) A, _LOG_H_VP2(F, A, b)
#define _LOG_H_VP4(F, A, a, b...) F(a) A, _LOG_H_VP3(F, A, b)
#define _LOG_H_VP5(F, A, a, b...) F(a) A, _LOG_H_VP4(F, A, b)
#define _LOG_H_VP6(F, A, a, b...) F(a) A, _LOG_H_VP5(F, A, b)
#define _LOG_H_VP7(F, A, a, b...) F(a) A, _LOG_H_VP6(F, A, b)
#define _LOG_H_VP8(F, A, a, b...) F(a) A, _LOG_H_VP7(F, A, b)
#define _LOG_H_VPn(F, A, vars...) _LOG_H_FE(vars, _LOG_H_VP8, _LOG_H_VP7, _LOG_H_VP6, _LOG_H_VP5, _LOG_H_VP4, _LOG_H_VP3, _LOG_H_VP2, _LOG_H_VP1)(F, A, vars)
#define _LOG_H_VP_(var) _LOG_H_V_ ## var
#define _LOG_H_VP(A, vars...) _LOG_H_VPn(_LOG_H_VP_, A, vars)

// MP = Module Parse
// Preprocessor can't recycle a generic MAP called "inside" itself, therefor we optimize stuff by creating two different, yet similar blocks of code
#define _LOG_H_MP1(F, A, a) F(A, a, a())
#define _LOG_H_MP2(F, A, a, b...) F(A, a, a()), _LOG_H_MP1(F, A, b)
#define _LOG_H_MP3(F, A, a, b...) F(A, a, a()), _LOG_H_MP2(F, A, b)
#define _LOG_H_MP4(F, A, a, b...) F(A, a, a()), _LOG_H_MP3(F, A, b)
#define _LOG_H_MP5(F, A, a, b...) F(A, a, a()), _LOG_H_MP4(F, A, b)
#define _LOG_H_MP6(F, A, a, b...) F(A, a, a()), _LOG_H_MP5(F, A, b)
#define _LOG_H_MP7(F, A, a, b...) F(A, a, a()), _LOG_H_MP6(F, A, b)
#define _LOG_H_MP8(F, A, a, b...) F(A, a, a()), _LOG_H_MP7(F, A, b)
#define _LOG_H_MPn(F, A, vars...) _LOG_H_FE(vars, _LOG_H_MP8, _LOG_H_MP7, _LOG_H_MP6, _LOG_H_MP5, _LOG_H_MP4, _LOG_H_MP3, _LOG_H_MP2, _LOG_H_MP1)(F, A, vars)
#define _LOG_H_MP_2(C, fmt, vars...) "%s" fmt RESET, C(vars), vars
#define _LOG_H_MP_1(A, C, fmt, vars...) _LOG_H_MP_2(C ## _COLOR, fmt, _LOG_H_VP(A, vars))
#define _LOG_H_MP_(A, C, mod) printf(_LOG_H_MP_1(A, C, mod))
#define _LOG_H_MP(A, mods...) _LOG_H_MPn(_LOG_H_MP_, A, mods)

#define _LOG_H_log(A, mods) _LOG_H_MP(A, mods)

/* End of magic tricks */

#define log(lvl, fmt, args...) _LOG_H_log((lvl, time(NULL)), MODULES()), printf(fmt "\n", ##args)

#define error(fmt, args...) log("error", fmt, args)
#define warn(fmt, args...) log("warn", fmt, args)
#define info(fmt, args...) log("info", fmt, args)
#define debug(fmt, args...) log("debug", fmt, args)

#endif