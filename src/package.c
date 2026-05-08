#include <string.h>
#include <stddef.h>
#include "../include/child.h"

    typedef struct {
        char *flag;
        char *path;
        char *args[6];
    } operations;

    static operations ops[] = {
        {"-i" , "rpm" , {"rpm", "-ql"} },
        {"-m" , "rpm" , {"rpm", "-qi"} },
        {"-d" , "rpm" , {"rpm", "-qR"} },
        {"-r" , "dnf" , {"dnf", "repoquery", "--whatrequires"} },
        {"-o" , "rpm" , {"rpm", "-qF"}},
        {NULL, NULL, {NULL}}
    };

    int packageAnalysis(const char* flag, char *package) {
        _Bool flagFound = 0;
        char * path; char *arg[8], **temp;
        for (int i = 0; ops[i].flag != NULL ; i++) {
            if (strcmp(flag, ops[i].flag) == 0) {
                path = ops[i].path;
                temp = ops[i].args;
                flagFound = 1;
                break;
            }
        }
        if (!flagFound) return 400;
        int t = 0;
        while ( t < 6 && temp[t] != NULL  ) {
            arg[t] = temp[t];
            ++t;
        }
        arg[t] = package;
        arg[++t] = NULL;

        if (task(path,arg) != 0 ) return 1;
        return 0;
}
