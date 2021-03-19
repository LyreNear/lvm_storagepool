#include "include.h"

int main() {
//    FILE *fp = NULL;
//    FILE *fh = NULL;
    char *buff = NULL;
    char *pacBuff = NULL;

/*    fp = popen("ls -la", "r");
    fh = fopen("shell.c", "w+");
    fread(buff, 1, 2047, fp);
    fwrite(buff, 1, 2047, fh);
    pclose(fp);
    fclose(fh);
    */

    pacBuff = (char *)malloc(2048);
    snprintf(pacBuff, 2048, "sudo pvdisplay -v");
    buff = sys_command_run_return(pacBuff);
    printf("%s\n", buff);
    return 0;
}
