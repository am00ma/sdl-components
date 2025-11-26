/** @file types.h
 *  @brief Type aliases and macros to make code readable.
 */
#pragma once
// clang-format off

#define DEBUG

/* ---------------------------------------------------------------------------
 * Common includes
 * ------------------------------------------------------------------------- */
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h> // IWYU pragma: keep
#include <SDL2/SDL.h>

typedef ptrdiff_t isize;
typedef size_t    usize;

typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef float    f32;
typedef double   f64;

/* ---------------------------------------------------------------------------
 * Aliases
 * ------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------
 * Range, i over n
 * ------------------------------------------------------------------------- */
#define RANGE(...) RANGEx(__VA_ARGS__, RANGE4, RANGE3, RANGE2, RANGE1)(__VA_ARGS__)
#define RANGEx(a, b, c, d, e, ...) e

#define RANGE1(i)          for (isize i = 0  ; i < 1  ; i++)
#define RANGE2(i, b)       for (isize i = 0  ; i < (b); i++)
#define RANGE3(i, a, b)    for (isize i = (a); i < (b); i++)
#define RANGE4(i, a, b, c) for (isize i = (a); i < (b); i += (c))

/* ---------------------------------------------------------------------------
 * Pretty output
 * ------------------------------------------------------------------------- */
#define COLOR_RESET   "\033[0m"
#define COLOR_BOLD    "\033[1m"
#define COLOR_ITALIC  "\033[3m"
#define COLOR_ULINE   "\033[4m"

#define COLOR_BLACK   "\033[0;30m"
#define COLOR_RED     "\033[0;31m"
#define COLOR_GREEN   "\033[0;32m"
#define COLOR_YELLOW  "\033[0;33m"
#define COLOR_BLUE    "\033[0;34m"
#define COLOR_MAGENTA "\033[0;35m"
#define COLOR_CYAN    "\033[0;36m"
#define COLOR_WHITE   "\033[0;37m"

// For printing %.*s
#define pstr(s) (int)s.len, s.buf
#define ppstr(s) (int)s->len, s->buf

// Log, pretty print, with/without Linebreak
#define p_log(...)         fprintf(stderr, __VA_ARGS__)
#define prettyl(color, ...) (p_log(color), p_log(__VA_ARGS__), p_log(COLOR_RESET"\n"))
#define pretty(color, ...)  (p_log(color), p_log(__VA_ARGS__), p_log(COLOR_RESET))

// Example to define style
#define STYLE_PTITLE COLOR_YELLOW COLOR_BOLD COLOR_ITALIC COLOR_ULINE
#define p_title(...) {p_log(STYLE_PTITLE); p_log(__VA_ARGS__); p_log(COLOR_RESET"\n");}
#define p_info(...)  {p_log(__VA_ARGS__);  p_log("\n");}
#define p_error(...) {p_log(COLOR_RED);    p_log(__VA_ARGS__); p_log(COLOR_RESET"\n");}

#ifdef DEBUG
#define p_debug(...)         prettyl(COLOR_WHITE, __VA_ARGS__)
#define pp_debug(color, ...) prettyl(color      , __VA_ARGS__)
#else
#define p_debug( ... )
#define pp_debug(color, ...)
#endif // DEBUG

#define print_(...) printx_(__VA_ARGS__, print4_, print3_, print2_, print1_)(__VA_ARGS__)
#define printx_(a, b, c, d, e, ...) e

#define print1_(x)          p_debug(   "%s: %ld", #x, x);
#define print2_(x, y)       p_debug(   "%s: " y , #x, x);
#define print3_(x, y, z)    p_debug( z "%s: " y , #x, x);
#define print4_(x, y, z, w) p_debug( z "%" #w "s: " y , #x, x);

#define print_range_header(vec, n, fmt) p_log("%10s -> ", #vec); RANGE(i, n) { p_log(fmt, i); } p_log("\n");
#define print_range(vec, n, fmt) p_log("%10s -> ", #vec); RANGE(i, n) { p_log(fmt, vec[i]); } p_log("\n");

/* ---------------------------------------------------------------------------
 * Normal Error handling -> prints to stderr
 * ------------------------------------------------------------------------- */
#define Free(x) if (x) { free(x); x = nullptr; }

#define p_err(err, behaviour, ...)            \
    if (err) {                                \
        p_error("%s:%d", __FILE__, __LINE__); \
        p_error(__VA_ARGS__);                 \
        behaviour;                            \
    }

#define Fatal( cond,  ...)      p_err(cond, exit(err) , __VA_ARGS__);
#define Return(err ,  ...)      p_err(err , return err, __VA_ARGS__);
#define RetVal(cond, val, ...)  p_err(cond, return val, __VA_ARGS__);
#define Goto( cond, label, ...) p_err(cond, goto label, __VA_ARGS__);

/* ---------------------------------------------------------------------------
 *  General asserts
 * ------------------------------------------------------------------------- */
// Debugger friendly assert
// https://nullprogram.com/blog/2022/06/26/
#define Assert(cond)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           \
    if (!(cond)) {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             \
        p_error("%s:%d", __FILE__, __LINE__);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   \
        p_error("Failed: %s", #cond);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           \
        __builtin_trap();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      \
    }

#define AssertMsg(cond, ...)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   \
    if (!(cond)) {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             \
        p_error("%s:%d", __FILE__, __LINE__);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   \
        p_error("Failed: %s", #cond);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           \
        p_error(__VA_ARGS__);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   \
        __builtin_trap();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      \
    }


/* ---------------------------------------------------------------------------
 *  Timing
 * ------------------------------------------------------------------------- */

#define Timestamp(t) struct timespec t; clock_gettime(CLOCK_MONOTONIC, &t)
#define ToSec(  t) ((f32)t.tv_sec + (f32)t.tv_nsec / 1e9)
#define ToMilli(t) ((u64)t.tv_sec * 1e6 + (u64)t.tv_nsec / 1e3)
#define ToNano( t) ((u64)t.tv_sec * 1e9 + (u64)t.tv_nsec)

// clang-format on
