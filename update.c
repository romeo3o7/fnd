#include <stdio.h>
#include <stdlib.h>
#include "include/child.h"

int checkUpdate() {
    printf("Checking update...\n");
    char *updateChecking[] = {"sudo" , "dnf" , "check-update" , "--refresh" , NULL};
    int checkStatus = task("sudo",updateChecking);
    if (checkStatus != 100 && checkStatus != 0) {
        fprintf(stderr ,"updating failed");
        return -1;
    }
    else if (checkStatus == 0) {
        printf("Up to date\n");
        return 1;
    }
    return 0;
}

int update() {
    printf("update found!\n");
    printf("would you like an offline or online update?\n");
    printf("offline if the update includes: kernel,libc,systemd,mesa.\n");
    char *online[] = { "sudo" , "dnf" , "upgrade" , NULL} , *offline[] = {"sudo" , "dnf" , "upgrade" , "--offline" , NULL};
    char **update;
    char buffer[8];
    int reboot = 0;
    while(1) {
        printf("'o' for online and 'f' for offline: ");
        fflush(stdout);
        char *input= fgets(buffer, sizeof(buffer) , stdin);
        if (input != NULL && (buffer[0] == 'o' || buffer[0] == 'f')) { // if pointer input is not null and first value of buffer is either 'o' or 'f'
            if (buffer[0] == 'f') {
                update = offline;
                reboot = 1;
            }
            else update = online;
            break;
        }
    }
    int updateStatus = task("sudo",update);
    if (updateStatus != 0) {
        fprintf(stderr,"upgrade failed, dnf stage");
        return -1;
    }

    printf("Update is done ... \n");
    return reboot;
}

int clearCache() {
    printf("clearing cache .. : ");
    fflush(stdout);
    char *arguments[] = {"sudo" , "dnf" , "clean" , "packages" , NULL};
    return task("sudo", arguments);
}

int clearOrphans() {
    printf("deleting orphaned packages : ");
    fflush(stdout);
    char *arguments[] = {"sudo" , "dnf" , "autoremove" , NULL};
    int orphanStatus = task("sudo" , arguments);
    if (orphanStatus == 0) printf("no orphaned packages found\n");
    else return 1;
    return 0;
}
int offlineActions() {
    char buffer[8];
    while (1) {
        printf("Offline transactions are avaliable would you like to update now? y/n: ");
        fflush(stdout);
        char *input = fgets(buffer, sizeof(buffer),stdin);
        if (input == NULL)     return -1;
        if (buffer[0] == 'n')  return 1;
        if (buffer[0] == 'y')  break;
    }
    char * argument[] = {"sudo", "dnf5" , "offline" , "reboot" , NULL};
    return task("sudo",argument);
}

int invoke_update() {
    int checkUpdateStatus = checkUpdate();
    if (checkUpdateStatus != 0) exit(0);
    int updateStaus = update();
    if (updateStaus == -1) return 1;
    int cacheStatus = clearCache();
    int clearOrphansStatsu = clearOrphans();
    if (updateStaus == 1) offlineActions();
    return 0;
}
