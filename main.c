#include <string.h>
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
        printf("  Structure: Package <option> <package/file>\n");
        printf("  Options:\n");
        printf("  < -f for installed >:   the files this package has installed.\n");
        printf("  < -m for metadata>:     the metadata of the package \n");
        printf("  < -d for depndency:     what this package requires to run\n");
        printf("  < -r for required:      packages that require it\n");
        printf("  < -o for own>:          packages who owns this file\n");
}

void echo_general() {
    printf("  Commands:\n");
    printf("  update:           update manager\n");
    printf("  package utility : package <flag> <package || file>\n");
    printf("  Use 'package' alone for flag details\n");
}
