#include <stdarg.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <ctype.h>


#include "tinylog.h"

static int log_initialized = 0;

static int log_level = TINY_LOG_DEBUG;
static tiny_log_listener_t log_listener = NULL;
static void* log_listener_arg = NULL;


static void log_add(int level, const void* buf, int bytes)
{

    if(log_listener){
        log_listener(log_listener_arg, level, buf, bytes + 1);
    }

}

static int log_init(int bytes, int level, tiny_log_listener_t listener, void* arg)
{

    log_level = level;
    log_listener = listener;
    log_listener_arg = arg;
    log_initialized = 1;
    return 0;

}

int tiny_log_set_level(int level)
{

    log_level = level;

    return 0;
}

int tiny_log_set_listener(tiny_log_listener_t listener, void* arg)
{

    log_listener = listener;
    log_listener_arg = arg;
    
    return 0;    
}

int tiny_log_init(int bytes, int level, tiny_log_listener_t listener, void* arg)
{

    return 0;
}


int tiny_log(const char* context, int level, const char* fmt, ...)
{
    int len;
    char buf[TINY_LOG_MAX_ENTRY_BYTES];
    va_list args;

    if(!log_initialized){
        log_init(TINY_LOG_BUFFER_BYTES, log_level, log_listener, log_listener_arg);
    }

    len = TINY_LOG_MAX_ENTRY_BYTES;
    len -= snprintf(buf, len, "%s : ", (context)? context : "");

    va_start(args, fmt);
    len -= vsnprintf(buf + TINY_LOG_MAX_ENTRY_BYTES - len, len, fmt, args);
    va_end(args);

    log_add(level, buf, TINY_LOG_MAX_ENTRY_BYTES - len);
}
