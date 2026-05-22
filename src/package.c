#include "../include/package.h"

static operations installed[] = {
    {"-f" , "rpm" , {"rpm", "-ql"} },
    {"-m" , "rpm" , {"rpm", "-qi"} },
    {"-d" , "rpm" , {"rpm", "-qR"} },
    {"-r" , "rpm" , {"rpm", "-q", "--whatrequires"} },
    {"-o" , "rpm" , {"rpm", "-qf"}},
    {NULL, NULL, {NULL}}
};
static operations notInstalled[] = {
	{"-f" , "dnf" , {"dnf", "repoquery" , "-l"} },
    {"-m" , "dnf" , {"dnf", "info"} },
    {"-d" , "dnf" , {"dnf", "repoquery" , "--requires"} },
    {"-r" , "dnf" , {"dnf", "repoquery", "--whatrequires"} },
    {"-o" , "dnf" , {"dnf", "provides"}},
    {NULL, NULL, {NULL}}
};

int packageAnalysis(const char* flag, char *package) {
    operations *array = checkInstalled(package) ? installed : notInstalled;
    _Bool flagFound = 0;
    char * path, *arg[8], **temp;
    for (int i = 0; array[i].flag != NULL ; i++) {
        if (strcmp(flag, array[i].flag) == 0) {
            path = array[i].path;
            temp = array[i].args;
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

bool checkInstalled(char *package) { // if this function returns 1 we query rpm, otherwise we query dnf
    size_t len = strlen(package);
    for (size_t i = 0; i < len; i++ ) {
        if (package[i] == '/') return access(package, F_OK) == 0; // if package has / then its a file, access to return 1 if it exists
    }
	char *args[] = {"rpm" , "-q" , package , NULL};
	int exits = silentTask("rpm" ,  args);
	if (exits == -1) exit(-1);
	return exits == 0;
}
