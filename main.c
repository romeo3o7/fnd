#include <string.h>
#include "include/package.h"
#include "include/update.h"

void echo_general();

int main (int argc, char *argv[]) {
    int status = 0;
    switch (argc) {
        case 1:
            echo_general();
            status = 1;
            break;

        case 2:
            if (strcmp(argv[1],"update") == 0) {
                return invoke_update();
            }
            echo_general();
            status = 1;
            break;

        case 3:
            if (strcmp(argv[1],"package") == 0) {
                fprintf(stderr,"You didn't specify a path/package\n");
            } else {
                echo_general();
            }
            status = 1;
            break;

        case 4:
           if (strcmp(argv[1] , "package") == 0 ) {
               char *flag = argv[2];
               char *string = "fmdro";
               for (int i = 0; i <= 4; i++){
                  if (flag[1] == string[i]) {
                       return packageAnalysis(argv[2],argv[3]);
                  }
               }
               status = 1;
               fprintf(stderr,"flag not found\n");
               break;
           }
           echo_general();
    }

    return status;
}

void echo_general() {
        printf("Commands:\n");
        printf("update:             update with no subcommands manages system update\n");
        printf("Package: \nStructure: <option> <package/file>\n");
        printf("Options:\n");
        printf("< -f for installed >:   what files the package installs.\n");
        printf("< -m for metadata>:     the metadata of the package \n");
        printf("< -d for depndency:     what this package depends on \n");
        printf("< -r for requires:      what requires this package\n");
        printf("< -o for own>:          who owns this file (only for files)\n");
}
