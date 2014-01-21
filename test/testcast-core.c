#include <stdio.h>
#include "tinylog.h"






static void print_components_by_name(void)
{
    
}



static void my_listener(void* arg,int level, void* log, int bytes)
{
    
    switch(level){
        case TINY_LOG_ERROR:
        case TINY_LOG_DEBUG:
            printf("%s", (char*)log);
    
        default:
            break;
    }
}


int main(int argc, char* arg[]){

    printf("hello world\n");

    tiny_log_set_listener(my_listener,NULL);

    TINYDBG("hello core\n");

    OMX_Init();

    print_components_by_name();

    return 0;

}

