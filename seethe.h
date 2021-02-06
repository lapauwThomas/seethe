#ifndef SEETHE_H
#define SEETHE_H

#include <stdio.h>
#include <time.h>

#ifndef LOG_LEVEL
    #define LOG_LEVEL       WARNING
#endif

#define DEBUG_COLOUR    ""
#define INFO_COLOUR     "\x1B[36m"
#define NOTICE_COLOUR   "\x1B[32;1m"
#define WARNING_COLOUR  "\x1B[33m"
#define ERROR_COLOUR    "\x1B[31m"
#define CRITICAL_COLOUR "\x1B[41;1m"

#define RESET_COLOUR    "\x1B[0m"

#define MSG_ENDING      "\n"
#define TIME_FORMAT     "%T "

#define DISPLAY_COLOUR  1
#define DISPLAY_TIME    1
#define DISPLAY_LEVEL   1
#define DISPLAY_FUNC    1
#define DISPLAY_FILE    1
#define DISPLAY_LINE    1

#define emit_log(colour, level, file, func, line, ...) do {                         \
    time_t raw_time;                                                                \
    time(&raw_time);                                                                \
    char time_buffer[80];                                                           \
    strftime(time_buffer, 80, TIME_FORMAT, localtime(&raw_time));                   \
                                                                                    \
    printf("%s", DISPLAY_COLOUR ? colour : "");                                     \
                                                                                    \
    printf("%s", DISPLAY_TIME ? time_buffer : "");                                  \
                                                                                    \
    printf("%s", DISPLAY_LEVEL ? level : "");                                       \
    printf("%s", DISPLAY_LEVEL ? " ": "");                                          \
                                                                                    \
    printf("%s", DISPLAY_FUNC ? func : "");                                         \
    printf("%s", DISPLAY_FUNC ? " " : "");                                          \
                                                                                    \
    printf("%s", DISPLAY_FILE || DISPLAY_LINE ? "(" : "");                          \
    printf("%s", DISPLAY_FILE ? file : "");                                         \
    printf("%s", DISPLAY_FILE && DISPLAY_LINE ? ":" : "");                          \
    printf("%.d", DISPLAY_LINE ? line : 0);                                         \
    printf("%s", DISPLAY_FILE || DISPLAY_LINE ? ") " : "");                         \
                                                                                    \
    printf("- ");                                                                   \
                                                                                    \
    printf(__VA_ARGS__);                                                            \
                                                                                    \
    printf("%s%s", RESET_COLOUR, MSG_ENDING);                                       \
} while (0)

#define DEBUG           0
#define INFO            1
#define NOTICE          2
#define WARNING         3
#define ERROR           4
#define CRITICAL        5

#define debug(...) do {                                                             \
    if (LOG_LEVEL == DEBUG) {                                                       \
        emit_log(                                                                   \
            DEBUG_COLOUR, "[DEBUG]", __FILE__, __func__, __LINE__, __VA_ARGS__      \
        );                                                                          \
    }                                                                               \
} while (0)

#define info(...) do {                                                              \
    if (LOG_LEVEL <= INFO) {                                                        \
        emit_log(                                                                   \
            INFO_COLOUR, "[INFO]", __FILE__, __func__, __LINE__, __VA_ARGS__        \
        );                                                                          \
    }                                                                               \
} while (0)

#define notice(...) do {                                                            \
    if (LOG_LEVEL <= NOTICE) {                                                      \
        emit_log(                                                                   \
            NOTICE_COLOUR, "[NOTICE]", __FILE__, __func__, __LINE__, __VA_ARGS__    \
        );                                                                          \
    }                                                                               \
} while (0)

#define warning(...) do {                                                           \
    if (LOG_LEVEL <= WARNING) {                                                     \
        emit_log(                                                                   \
            WARNING_COLOUR, "[WARNING]", __FILE__, __func__, __LINE__, __VA_ARGS__  \
        );                                                                          \
    }                                                                               \
} while (0)

#define error(...) do {                                                             \
    if (LOG_LEVEL <= ERROR) {                                                       \
        emit_log(                                                                   \
            ERROR_COLOUR, "[ERROR]", __FILE__, __func__, __LINE__, __VA_ARGS__      \
        );                                                                          \
    }                                                                               \
} while (0)

#define critical(...) do {                                                          \
    emit_log(                                                                       \
        CRITICAL_COLOUR, "[CRITICAL]", __FILE__, __func__, __LINE__, __VA_ARGS__    \
    );                                                                              \
} while (0)

#endif // seethe.h
