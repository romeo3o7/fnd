#include <string.h>
#include "../include/package.h"
#include "../include/update.h"

static void echo_general(void) {
		char msg[] = "fnd update:\tmanages system update\n"
			"fnd package <option> <package/file>:\nchecks for package/file specifed option\n\n"
			"options:\n"
			"f\twhat files the package installed\n"
			"m\tthe metadata of the package\n"
			"d\twhat this package depends on\n"
			"r\twhat requires this package\n"
			"o\twho owns this file (only for\n";
        printf("%s",msg);
}

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
                fprintf(stderr,"Make sure the flag is right and specify package/file\n");
            } else {
                echo_general();
            }
            status = 1;
            break;

        case 4:
           if (strcmp(argv[1] , "package") == 0 ) {
               char *flag = argv[2];
               char *string[6] = {"f","m","d","r","o"};

               for (int i = 0; i <= 4; i++){
				  if (strcmp(flag, string[i]) == 0 ) {
                       return packageAnalysis(flag,argv[3]);
                  }
               }
               status = 1;
               fprintf(stderr,"flag not found\n");
               break;
           }
           echo_general();
		   break;
		default: break;
    }

    return status;
}
