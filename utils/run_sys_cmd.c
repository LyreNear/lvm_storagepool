#include "include.h"

static pthread_key_t g_thcmdkey;

static void utils_free_buff(void *buff) {
    fprintf(stderr, "Free the buffer %p %p.\n", buff, (void *)pthread_self());
    free(buff);
    return;
}

__attribute((constructor)) int utils_init(VOID) {
    pthread_key_create(&g_thcmdkey, utils_free_buff);
    return 0;
}

char *sys_command_run_return(char* _acCMD) {
    FILE *fFp = NULL;
    strcat(_acCMD, " 2>&1 ");
    char *pcRet = pthread_getspecific(g_thcmdkey);
    size_t iRead = 0;

    if (!pcRet) {
        pcRet = (char *)malloc(2048);
        if (NULL == pcRet) {
            printf("Not enough space for return result alloc!\n");
            return NULL;
        }
        pthread_setspecific(g_thcmdkey, pcRet);
    }
    memset(pcRet, 0, 2048);

    if (NULL == (fFp = popen(_acCMD, "r"))) {
        return NULL;
    }

    if (NULL != fFp) {
        iRead = fread(pcRet, 2048, 1, fFp);
        if (0 > iRead) {
            pcRet = NULL;
        }
        pclose(fFp);
    }
    return pcRet;
}

