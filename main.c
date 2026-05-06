#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/package.h"
#include "include/update.h"

void echo_general();
void echo_package();

int main (int argc, char *argv[]) {
    int status = 0;
    if (argc == 1) {
        echo_general();
        exit(1);
    }
    else if (argc == 2) {
        if (strcmp(argv[1],"update") == 0) status = invoke_update();
        else if (strcmp(argv[1],"package") == 0) echo_package();
        else {
            echo_general();
            exit(1);
        }
    }
    else if (argc >= 4 ) {
        if (strcmp(argv[1],"package") == 0) {
            status = packageAnalysis(argv[2] , argv[3]);
            if (status == 400) fprintf(stderr,"Flag not found");
        }
        else echo_general();
    }
    else echo_general();
    return status;
}

void echo_package() {
        fprintf(stderr, "  Structure: Package <option> <package/file>\n");
        fprintf(stderr, "  Options:\n");
        fprintf(stderr, "  < -i for installed >:   the files this package has installed.\n");
        fprintf(stderr, "  < -m for metadata>:     the metadata of the package \n");
        fprintf(stderr, "  < -d for depndency:     what this package requires to run\n");
        fprintf(stderr, "  < -r for required:      packages that require it\n");
        fprintf(stderr, "  < -o for own>:          packages who owns this file\n");
}

void echo_general() {
    fprintf(stderr, "  Commands:\n");
    fprintf(stderr, "  update:           update manager\n");
    fprintf(stderr, "  package utility : package <flag> <package || file>\n");
    fprintf(stderr, "  Use 'package' alone for flag details\n");
}
