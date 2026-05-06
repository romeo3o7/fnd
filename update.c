#include <ctype.h>
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
    printf("would you like an offline or local update?\n");
    printf("offline if the update includes: kernel,libc,systemd,mesa.\n");
    char *online[] = { "sudo" , "dnf" , "upgrade" , NULL} , *offline[] = {"sudo" , "dnf" , "upgrade" , "--offline" , NULL};
    char **update;
    char buffer[8];
    int reboot = 0;
    while(1) {
        printf("'l' for local and 'f' for offline [l/f]? ");
        fflush(stdout);
        char *input= fgets(buffer, sizeof(buffer) , stdin);
        if (input == NULL) return -1;
        char c = tolower(buffer[0]);
        if (c == 'l' || c == 'f') {
            update = (c == 'f') ?  offline : online;
            reboot = (c == 'f');
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

int clearCache() { // future improvment to only delete all packages on the third update
    printf("clearing cache .. : ");
    fflush(stdout);
    char *arguments[] = {"sudo" , "dnf" , "clean" , "all" , NULL};
    return task("sudo", arguments);
}

int clearOrphans() {
    printf("deleting orphaned packages : ");
    fflush(stdout);
    char *arguments[] = {"sudo" , "dnf" , "autoremove" , NULL};
    int orphanStatus = task("sudo" , arguments);
    if (orphanStatus == 0) printf("no orphaned packages found\n");
    return 0;
}
int offlineActions() {
    char buffer[8];
    while (1) {
        printf("Offline transactions are avaliable would you like to update now [y/n]?  ");
        fflush(stdout);
        char *input = fgets(buffer, sizeof(buffer),stdin);
        char c = tolower(buffer[0]);
        if (input == NULL)     return -1;
        if (c == 'n')          return 1;
        if (c == 'y')          break;
    }
    char * argument[] = {"sudo", "dnf5" , "offline" , "reboot" , NULL};
    int status = task("sudo",argument);
    if (status != 0) {
        fprintf(stderr, "dnf5 is not installed\n");
        return 1;
    }
   return 0;
}

int invoke_update() {
    int checkUpdateStatus = checkUpdate();
    if (checkUpdateStatus != 0) return checkUpdateStatus;
    int updateStaus = update();
    if (updateStaus == -1) return -1;
    int cacheStatus = clearCache();
    int clearOrphansStatsu = clearOrphans();
    if (updateStaus == 1) return offlineActions();
    return 0;
}
