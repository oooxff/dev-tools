#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

static void show_browser_pid(char *buffer)
{
    char *ret;
    int count = 0;

    while((ret = strsep(&buffer, " ")) != NULL) {
        if (ret[0] == 0) {
            continue;
        }

        if (count == 3) {
            printf("%s\n", ret);
            break;
        }

        count ++;
    }
}

int main(int argc, char *argv[])
{
    FILE *fp;
    char buffer[4096];
    const char *cmd = "adb shell b2g-ps";

    if ((fp = popen(cmd, "r")) == NULL) {
        perror("popen failed");
        exit(1);
    }

    while(fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (! strncmp(buffer, "Browser", 7)) {
            show_browser_pid(buffer);
        } else if (! strncmp(buffer, "CastApp", 7)) {
            show_browser_pid(buffer);
        }
    }

    pclose(fp);
    return 0;
}

