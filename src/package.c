#include "../include/package.h"
#include <sys/types.h>

static operations installed[] = {
    {'f' , "rpm" , {"rpm", "-ql", NULL} },
    {'m' , "rpm" , {"rpm", "-qi", NULL} },
    {'d' , "rpm" , {"rpm", "-qR", NULL} },
    {'r' , "rpm" , {"rpm", "-q", "--whatrequires" , NULL} },
    {'o' , "rpm" , {"rpm", "-qf" , NULL}},
};
static operations notInstalled[] = {
    {'f' , "dnf" , {"dnf", "repoquery" , "-l" , NULL} },
    {'m' , "dnf" , {"dnf", "info", NULL} },
    {'d' , "dnf" , {"dnf", "repoquery" , "--requires" , NULL} },
    {'r' , "dnf" , {"dnf", "repoquery", "--whatrequires" , NULL} },
    {'o' , "dnf" , {"dnf", "provides", NULL}},
};

int packageAnalysis(const char* flag, char *package) {
    operations *array = checkInstalled(package) ? installed : notInstalled;
    char * path  = NULL;
	char *arg[8];
	char **temp  = NULL;
    for (int i = 0; i < 5; i++) {
        if (flag[0] == array[i].flag) {
            path = array[i].path;
            temp = array[i].args;
            break;
        }
    }
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

bool checkInstalled(char *package) { // if this function returns 1 we query rpm, otherwise we query dnf
    unsigned int len = 0;
    while(package[len] != '\0') {
        len++;
    }

    for (size_t i = 0; i < len; i++ ) {
        if (package[i] == '/') return access(package, F_OK) == 0; // if package has / then its a file, access to return 1 if it exists
    }
	char *args[] = {"rpm" , "-q" , package , NULL};
	int exits = silentTask("rpm" ,  args);
	if (exits == -1) exit(-1);
	return exits == 0;
}
