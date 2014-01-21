#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <syslog.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

#define TINY_LOG_DISABLED   -1
#define TINY_LOG_FATAL      0

#define TINY_LOG_ERROR      8
#define TINY_LOG_WARNING    16
#define TINY_LOG_INFO       32
#define TINY_LOG_VERBOSE    64
#define TINY_LOG_DEBUG      999

#define TINY_LOG_MAX_ENTRY_BYTES (2*1024)


#define TINY_LOG_BUFFER_BYTES (2*1024*1024)


typedef void (*tiny_log_listener_t)(void* arg,
                                int level, void* log, int bytes);


/*
*   log module interface 
*/

int tiny_log_init(int bytes, int level, tiny_log_listener_t listener, void* arg);

int tiny_log(const char* context, int level, const char* fmt, ...);

int tiny_log_set_level(int level);

int tiny_log_get_level(void);

int tiny_log_set_listener(tiny_log_listener_t listener, void* arg);

int tiny_log_read(void* log, int* bytes);

void tiny_log_dump(void);


/*
*   log module macro
*/
#define TINYLOG(level, descriptor, fmt, arg...) do {                     \
        char context[1024];                                             \
        snprintf(context, 1024, "%s: %s--%s: %d",                       \
                 descriptor, __BASE_FILE__, __FUNCTION__, __LINE__);    \
        tiny_log(context, level, fmt, ##arg); } while(0)


#define  TINYERR(fmt, arg...)   TINYLOG(TINY_LOG_ERROR, "ERROR", fmt, ##arg)
#define  TINYDBG(fmt, arg...)   TINYLOG(TINY_LOG_DEBUG, "DEBUG", fmt, ##arg)


#endif