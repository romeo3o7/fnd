#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "include/child.h"

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
        {"-o" , "rpm" , {"rpm", "-qF"}}
    };

    int packageAnalysis(const char* flag, char *package) {
        char * path; char **arg, **temp;
        for (size_t i = 0; i < 5; i++) {
            if (strcmp(flag, ops[i].flag) == 0) {
                path = ops[i].path;
                temp = ops[i].args;
                break;
            }
        }
        size_t t = 0;
        while (temp != NULL && t < 6 ) {
            arg[t] = temp[t];
            ++t;
        }
        arg[t] = package;
        arg[++t] = NULL;

        int status = task(path,arg);
        return status;
}
